
if(WISDOM_WINDOWS)
	message("Platform Library is DirectX 12")
	set(WISDOM_DX12 TRUE)
	
	wisdom_sources(TARGET ${PROJECT_NAME}
		HEADERS 
			"include/wisdom/xdx12/dx12_factory.h"
			"include/wisdom/xdx12/dx12_views.h"
			"include/wisdom/xdx12/dx12_adapter.h"
			"include/wisdom/xdx12/dx12_info.h"
			"include/wisdom/xdx12/dx12_checks.h"
			"include/wisdom/xdx12/dx12_convert.h"
			"include/wisdom/xdx12/dx12_fence.h"
			"include/wisdom/xdx12/dx12_device.h"
			"include/wisdom/xdx12/dx12_command_queue.h"
			"include/wisdom/xdx12/dx12_command_list.h"
			"include/wisdom/xdx12/dx12_descriptor_buffer.h"
			"include/wisdom/xdx12/dx12_root_signature.h"
			"include/wisdom/xdx12/dx12_resource.h"
			"include/wisdom/xdx12/dx12_shader.h"
			"include/wisdom/xdx12/dx12_allocator.h"
			"include/wisdom/xdx12/dx12_swapchain.h"
			"include/wisdom/xdx12/dx12_debug.h"
		SOURCES
			"include/wisdom/xdx12/impl/dx12_allocator.cpp"
			"include/wisdom/xdx12/impl/dx12_factory.cpp"
			"include/wisdom/xdx12/impl/dx12_info.cpp"
			"include/wisdom/xdx12/impl/dx12_fence.cpp"
			"include/wisdom/xdx12/impl/dx12_device.cpp"
			"include/wisdom/xdx12/impl/dx12_swapchain.cpp"
			"include/wisdom/xdx12/impl/dx12_command_list.cpp"
		LIBS
			DX12Agility
			DX12Allocator
			d3d12
			d3d11
			DXGI
			DXGUID
	)
endif()
