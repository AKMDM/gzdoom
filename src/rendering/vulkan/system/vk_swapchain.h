#pragma once

#include "vk_device.h"

class VulkanSemaphore;
class VulkanFence;

class VulkanSwapChain
{
public:
	VulkanSwapChain(VulkanDevice *device);
	~VulkanSwapChain();

	uint32_t AcquireImage(int width, int height, VulkanSemaphore *semaphore = nullptr, VulkanFence *fence = nullptr);
	void QueuePresent(uint32_t imageIndex, VulkanSemaphore *semaphore = nullptr);

	void Recreate();

	bool vsync;
	VkSwapchainKHR swapChain = VK_NULL_HANDLE;
	VkSurfaceFormatKHR swapChainFormat;
	VkPresentModeKHR swapChainPresentMode;

	std::vector<VkImage> swapChainImages;
	std::vector<VkImageView> swapChainImageViews;

	VkExtent2D actualExtent;

private:
	void SelectFormat();
	void SelectPresentMode();
	bool CreateSwapChain(VkSwapchainKHR oldSwapChain = VK_NULL_HANDLE);
	void CreateViews();
	void SetHdrMetadata();
	void GetImages();
	void ReleaseResources();
	void ReleaseViews();

	VkSurfaceCapabilitiesKHR GetSurfaceCapabilities();
	std::vector<VkSurfaceFormatKHR> GetSurfaceFormats();
	std::vector<VkPresentModeKHR> GetPresentModes();

	VulkanDevice *device = nullptr;

	int lastSwapWidth = 0;
	int lastSwapHeight = 0;

	VulkanSwapChain(const VulkanSwapChain &) = delete;
	VulkanSwapChain &operator=(const VulkanSwapChain &) = delete;
};
