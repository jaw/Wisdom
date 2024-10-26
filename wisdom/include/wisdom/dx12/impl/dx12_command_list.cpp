#ifndef WIS_DX12_COMMAND_LIST_CPP
#define WIS_DX12_COMMAND_LIST_CPP
#include <wisdom/dx12/dx12_command_list.h>

#include <wisdom/dx12/dx12_checks.h>
#include <wisdom/generated/dx12/dx12_structs.hpp>
#include <wisdom/util/small_allocator.h>
#include <d3dx12/d3dx12_resource_helpers.h>
#include <d3dx12/d3dx12_root_signature.h>

void wis::ImplDX12CommandList::CopyBuffer(DX12BufferView source, DX12BufferView destination, wis::BufferRegion region) const noexcept
{
    list->CopyBufferRegion(std::get<0>(destination), region.dst_offset, std::get<0>(source), region.src_offset, region.size_bytes);
}
void wis::ImplDX12CommandList::CopyBufferToTexture(DX12BufferView src_buffer, DX12TextureView dest_texture, const wis::BufferTextureCopyRegion* regions, uint32_t region_count) const noexcept
{
    auto texture = std::get<0>(dest_texture);
    auto texture_desc = texture->GetDesc();

    wis::com_ptr<ID3D12Device> device;
    auto hr = texture->GetDevice(__uuidof(*device), device.put_void());

    for (uint32_t i = 0; i < region_count; i++) {
        auto& region = regions[i];
        D3D12_PLACED_SUBRESOURCE_FOOTPRINT layout{};
        UINT num_rows = 0;
        UINT64 row_size = 0;
        UINT64 required_size = 0;

        UINT dest_subresource = D3D12CalcSubresource(region.texture.mip, region.texture.array_layer, 0u, texture_desc.MipLevels, texture_desc.DepthOrArraySize);
        D3D12_TEXTURE_COPY_LOCATION dst{
            .pResource = texture,
            .Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX,
            .SubresourceIndex = dest_subresource
        };

        UINT row_pitch = 0;
        D3D12_PROPERTY_LAYOUT_FORMAT_TABLE::CalculateMinimumRowMajorRowPitch(convert_dx(region.texture.format), region.texture.size.width, row_pitch);

        D3D12_TEXTURE_COPY_LOCATION src{
            .pResource = std::get<0>(src_buffer),
            .Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT,
            .PlacedFootprint = {
                    .Offset = region.buffer_offset,
                    .Footprint = {
                            .Format = convert_dx(region.texture.format),
                            .Width = region.texture.size.width,
                            .Height = region.texture.size.height,
                            .Depth = region.texture.size.depth_or_layers,
                            .RowPitch = row_pitch } }
        };

        list->CopyTextureRegion(&dst, region.texture.offset.width, region.texture.offset.height, region.texture.offset.depth_or_layers, &src, nullptr);
    }
}

void wis::ImplDX12CommandList::CopyTextureToBuffer(DX12TextureView src_texture, DX12BufferView dest_buffer, const wis::BufferTextureCopyRegion* regions, uint32_t region_count) const noexcept
{
    auto texture = std::get<0>(src_texture);
    auto texture_desc = texture->GetDesc();

    wis::com_ptr<ID3D12Device> device;
    auto hr = texture->GetDevice(__uuidof(*device), device.put_void());

    for (uint32_t i = 0; i < region_count; i++) {
        auto& region = regions[i];
        D3D12_PLACED_SUBRESOURCE_FOOTPRINT layout{};
        UINT num_rows = 0;
        UINT64 row_size = 0;
        UINT64 required_size = 0;

        UINT src_subresource = D3D12CalcSubresource(region.texture.mip, region.texture.array_layer, 0u, texture_desc.MipLevels, texture_desc.DepthOrArraySize);
        D3D12_TEXTURE_COPY_LOCATION src{
            .pResource = texture,
            .Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX,
            .SubresourceIndex = src_subresource
        };

        UINT row_pitch = 0;
        D3D12_PROPERTY_LAYOUT_FORMAT_TABLE::CalculateMinimumRowMajorRowPitch(convert_dx(region.texture.format), region.texture.size.width, row_pitch);

        D3D12_TEXTURE_COPY_LOCATION dst{
            .pResource = std::get<0>(dest_buffer),
            .Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT,
            .PlacedFootprint = {
                    .Offset = region.buffer_offset,
                    .Footprint = {
                            .Format = convert_dx(region.texture.format),
                            .Width = region.texture.size.width,
                            .Height = region.texture.size.height,
                            .Depth = region.texture.size.depth_or_layers,
                            .RowPitch = row_pitch } }
        };

        list->CopyTextureRegion(&dst, UINT(region.buffer_offset), 0, 0, &src, nullptr);
    }
}

wis::Result wis::ImplDX12CommandList::Reset(wis::DX12PipelineView pipeline) noexcept
{
    Close();

    auto hr = allocator->Reset();
    if (!wis::succeeded(hr)) {
        return wis::make_result<FUNC, "Reset failed (allocator)">(hr);
    }

    hr = list->Reset(allocator.get(), std::get<0>(pipeline));
    closed = false;
    return wis::succeeded(hr) ? wis::success : wis::make_result<FUNC, "Reset failed (command list)">(hr);
}

void wis::ImplDX12CommandList::SetPipelineState(wis::DX12PipelineView pipeline) noexcept
{
    list->SetPipelineState(std::get<0>(pipeline));
}

bool wis::ImplDX12CommandList::Close() noexcept
{
    if (closed) {
        return true;
    }
    return closed = succeeded(list->Close());
}

namespace wis::detail {
inline D3D12_BUFFER_BARRIER to_dx(wis::BufferBarrier barrier, ID3D12Resource* buffer) noexcept
{
    return D3D12_BUFFER_BARRIER{
        .SyncBefore = convert_dx(barrier.sync_before),
        .SyncAfter = convert_dx(barrier.sync_after),
        .AccessBefore = convert_dx(barrier.access_before),
        .AccessAfter = convert_dx(barrier.access_after),
        .pResource = buffer,
        .Offset = barrier.offset,
        .Size = barrier.size
    };
}
inline D3D12_TEXTURE_BARRIER to_dx(wis::TextureBarrier barrier, ID3D12Resource* buffer) noexcept
{
    auto& subresource = barrier.subresource_range;
    bool zero_range = subresource.base_array_layer == 0 && subresource.base_mip_level == 0 && subresource.layer_count == 0 && subresource.level_count == 0;

    return D3D12_TEXTURE_BARRIER{
        .SyncBefore = convert_dx(barrier.sync_before),
        .SyncAfter = convert_dx(barrier.sync_after),
        .AccessBefore = convert_dx(barrier.access_before),
        .AccessAfter = convert_dx(barrier.access_after),
        .LayoutBefore = convert_dx(barrier.state_before),
        .LayoutAfter = convert_dx(barrier.state_after),
        .pResource = buffer,
        .Subresources = zero_range ? D3D12_BARRIER_SUBRESOURCE_RANGE{ .IndexOrFirstMipLevel = 0xffffffff }
                                   : D3D12_BARRIER_SUBRESOURCE_RANGE{
                                             .IndexOrFirstMipLevel = subresource.base_mip_level,
                                             .NumMipLevels = subresource.level_count,
                                             .FirstArraySlice = subresource.base_array_layer,
                                             .NumArraySlices = subresource.layer_count,
                                             .FirstPlane = 0,
                                             .NumPlanes = 1 }
    };
}
} // namespace wis::detail

void wis::ImplDX12CommandList::BufferBarrier(wis::BufferBarrier barrier, DX12BufferView buffer) noexcept
{
    D3D12_BUFFER_BARRIER bb = detail::to_dx(barrier, std::get<0>(buffer));
    D3D12_BARRIER_GROUP bg{
        .Type = D3D12_BARRIER_TYPE_BUFFER,
        .NumBarriers = 1,
        .pBufferBarriers = &bb
    };
    list->Barrier(1, &bg);
}

void wis::ImplDX12CommandList::BufferBarriers(const wis::DX12BufferBarrier2* barriers, uint32_t barrier_count) noexcept
{
    wis::detail::limited_allocator<D3D12_BUFFER_BARRIER, 8> allocator(barrier_count, true);
    auto* data = allocator.data();

    for (size_t i = 0; i < barrier_count; i++) {
        data[i] = detail::to_dx(barriers[i].barrier, std::get<0>(barriers[i].buffer));
    }

    D3D12_BARRIER_GROUP bg{
        .Type = D3D12_BARRIER_TYPE_BUFFER,
        .NumBarriers = barrier_count,
        .pBufferBarriers = data
    };
    list->Barrier(1, &bg);
}

void wis::ImplDX12CommandList::TextureBarrier(wis::TextureBarrier barrier, DX12TextureView texture) noexcept
{
    D3D12_TEXTURE_BARRIER tb = detail::to_dx(barrier, std::get<0>(texture));
    D3D12_BARRIER_GROUP bg{
        .Type = D3D12_BARRIER_TYPE_TEXTURE,
        .NumBarriers = 1,
        .pTextureBarriers = &tb
    };
    list->Barrier(1, &bg);
}
void wis::ImplDX12CommandList::TextureBarriers(const wis::DX12TextureBarrier2* barrier, uint32_t barrier_count) noexcept
{
    wis::detail::limited_allocator<D3D12_TEXTURE_BARRIER, 8> allocator(barrier_count, true);
    auto* data = allocator.data();

    for (size_t i = 0; i < barrier_count; i++) {
        data[i] = detail::to_dx(barrier[i].barrier, std::get<0>(barrier[i].texture));
    }

    D3D12_BARRIER_GROUP bg{
        .Type = D3D12_BARRIER_TYPE_TEXTURE,
        .NumBarriers = barrier_count,
        .pTextureBarriers = data
    };
    list->Barrier(1, &bg);
}

void wis::ImplDX12CommandList::BeginRenderPass(const wis::DX12RenderPassDesc* pass_desc) noexcept
{
    wis::detail::limited_allocator<D3D12_RENDER_PASS_RENDER_TARGET_DESC, 8> allocator(8, true);
    auto* data = allocator.data();

    for (size_t i = 0; i < pass_desc->target_count; i++) {
        auto& target = pass_desc->targets[i];
        data[i] = {
            .cpuDescriptor = std::get<0>(target.target),
            .BeginningAccess = {
                    .Type = convert_dx(target.load_op),
            },
            .EndingAccess = {
                    .Type = convert_dx(target.store_op),
            }
        };
        if (data[i].BeginningAccess.Type == D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE_CLEAR) {
            std::copy(std::begin(target.clear_value), std::end(target.clear_value), std::begin(data[i].BeginningAccess.Clear.ClearValue.Color));
        }
    }

    if (pass_desc->depth_stencil) {
        auto ds_selector = pass_desc->depth_stencil->depth_stencil_select;

        D3D12_RENDER_PASS_DEPTH_STENCIL_DESC depth_stencil{
            .cpuDescriptor = std::get<0>(pass_desc->depth_stencil->target),
            .DepthBeginningAccess = {
                    .Type = ds_selector & DSSelect::Depth ? convert_dx(pass_desc->depth_stencil->load_op_depth) : D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE_NO_ACCESS,
                    .Clear = {
                            .ClearValue{
                                    .DepthStencil{
                                            .Depth = pass_desc->depth_stencil->clear_depth,
                                            .Stencil = pass_desc->depth_stencil->clear_stencil } } },
            },
            .StencilBeginningAccess = { .Type = ds_selector & DSSelect::Stencil ? convert_dx(pass_desc->depth_stencil->load_op_stencil) : D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE_NO_ACCESS, .Clear = { .ClearValue{ .DepthStencil{ .Depth = pass_desc->depth_stencil->clear_depth, .Stencil = pass_desc->depth_stencil->clear_stencil } } } },
            .DepthEndingAccess = {
                    .Type = ds_selector & DSSelect::Depth ? convert_dx(pass_desc->depth_stencil->store_op_depth) : D3D12_RENDER_PASS_ENDING_ACCESS_TYPE_NO_ACCESS,
            },
            .StencilEndingAccess = {
                    .Type = ds_selector & DSSelect::Stencil ? convert_dx(pass_desc->depth_stencil->store_op_stencil) : D3D12_RENDER_PASS_ENDING_ACCESS_TYPE_NO_ACCESS,
            }
        };

        return list->BeginRenderPass(pass_desc->target_count, data, (ds_selector != DSSelect::None) ? &depth_stencil : nullptr, convert_dx(pass_desc->flags));
    }
    list->BeginRenderPass(pass_desc->target_count, data, nullptr, convert_dx(pass_desc->flags));
}

void wis::ImplDX12CommandList::EndRenderPass() noexcept
{
    list->EndRenderPass();
}

void wis::ImplDX12CommandList::IASetPrimitiveTopology(wis::PrimitiveTopology vp) noexcept
{
    list->IASetPrimitiveTopology(convert_dx(vp));
}

void wis::ImplDX12CommandList::IASetVertexBuffers(const wis::DX12VertexBufferBinding* resources, uint32_t count, uint32_t start_slot) noexcept
{
    wis::detail::limited_allocator<D3D12_VERTEX_BUFFER_VIEW, 8> allocator(count, true);
    auto* data = allocator.data();
    for (size_t i = 0; i < count; i++) {
        const DX12VertexBufferBinding& resource = resources[i];
        data[i] = {
            .BufferLocation = std::get<0>(resource.buffer)->GetGPUVirtualAddress() + resource.offset,
            .SizeInBytes = resources[i].size,
            .StrideInBytes = resources[i].stride
        };
    }

    list->IASetVertexBuffers(start_slot, count, data);
}

void wis::ImplDX12CommandList::IASetIndexBuffer(wis::DX12BufferView buffer, wis::IndexType type, uint64_t offset) noexcept
{
    D3D12_INDEX_BUFFER_VIEW ibv{
        .BufferLocation = std::get<0>(buffer)->GetGPUVirtualAddress() + offset,
        .SizeInBytes = uint32_t(std::get<0>(buffer)->GetDesc().Width),
        .Format = convert_dx(type)
    };
    list->IASetIndexBuffer(&ibv);
}
void wis::ImplDX12CommandList::IASetIndexBuffer2(wis::DX12BufferView buffer, wis::IndexType type, uint32_t size, uint64_t offset) noexcept
{
    D3D12_INDEX_BUFFER_VIEW ibv{
        .BufferLocation = std::get<0>(buffer)->GetGPUVirtualAddress() + offset,
        .SizeInBytes = size,
        .Format = convert_dx(type)
    };
    list->IASetIndexBuffer(&ibv);
}

void wis::ImplDX12CommandList::RSSetViewport(wis::Viewport vp) noexcept
{
    D3D12_VIEWPORT viewport{
        .TopLeftX = vp.top_leftx,
        .TopLeftY = vp.top_lefty,
        .Width = vp.width,
        .Height = vp.height,
        .MinDepth = vp.min_depth,
        .MaxDepth = vp.max_depth
    };
    list->RSSetViewports(1, &viewport);
}
void wis::ImplDX12CommandList::RSSetViewports(const wis::Viewport* vp, uint32_t count) noexcept
{
    static_assert(sizeof(D3D12_VIEWPORT) == sizeof(wis::Viewport));
    list->RSSetViewports(count, reinterpret_cast<const D3D12_VIEWPORT*>(vp));
}

void wis::ImplDX12CommandList::RSSetScissor(wis::Scissor sc) noexcept
{
    D3D12_RECT rect{
        .left = static_cast<LONG>(sc.left),
        .top = static_cast<LONG>(sc.top),
        .right = static_cast<LONG>(sc.right),
        .bottom = static_cast<LONG>(sc.bottom)
    };
    list->RSSetScissorRects(1, &rect);
}
void wis::ImplDX12CommandList::RSSetScissors(const wis::Scissor* vp, uint32_t count) noexcept
{
    static_assert(sizeof(D3D12_RECT) == sizeof(wis::Scissor));
    list->RSSetScissorRects(count, reinterpret_cast<const D3D12_RECT*>(vp));
}

void wis::ImplDX12CommandList::SetRootSignature(wis::DX12RootSignatureView root_signature) noexcept
{
    list->SetGraphicsRootSignature(std::get<0>(root_signature));
    root_stage_map = std::get<1>(root_signature);
    root_table_offset = std::get<2>(root_signature);
}

void wis::ImplDX12CommandList::DrawIndexedInstanced(uint32_t vertex_count_per_instance,
                                                    uint32_t instance_count,
                                                    uint32_t start_index,
                                                    uint32_t base_vertex,
                                                    uint32_t start_instance) noexcept
{
    list->DrawIndexedInstanced(vertex_count_per_instance, instance_count, start_index, base_vertex, start_instance);
}

void wis::ImplDX12CommandList::DrawInstanced(uint32_t vertex_count_per_instance,
                                             uint32_t instance_count,
                                             uint32_t base_vertex,
                                             uint32_t start_instance) noexcept
{
    list->DrawInstanced(vertex_count_per_instance, instance_count, base_vertex, start_instance);
}

void wis::ImplDX12CommandList::SetRootConstants(const void* data, uint32_t size_4bytes, uint32_t offset_4bytes, wis::ShaderStages stage) noexcept
{
    list->SetGraphicsRoot32BitConstants(UINT(root_stage_map[uint32_t(stage)]), size_4bytes, data, offset_4bytes);
}

void wis::ImplDX12CommandList::SetDescriptorBuffers(const wis::DX12DescriptorBufferView* buffers, uint32_t buffer_count) noexcept
{
    list->SetDescriptorHeaps(buffer_count, reinterpret_cast<ID3D12DescriptorHeap* const*>(buffers));
}

void wis::ImplDX12CommandList::SetDescriptorTableOffset(uint32_t root_table_index, wis::DX12DescriptorBufferGPUView buffer, uint32_t offset_bytes) noexcept
{
    auto handle = std::get<0>(buffer);
    list->SetGraphicsRootDescriptorTable(root_table_offset + root_table_index,
                                         CD3DX12_GPU_DESCRIPTOR_HANDLE(handle, offset_bytes));
}

#endif // WIS_DX12_COMMAND_LIST_H
