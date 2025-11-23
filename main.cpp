#include <vulkan/vulkan.h>
#include<GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<vector>
const uint32_t WIDTH  = 800;
const uint32_t HEIGHT = 600;

typedef struct App{
	GLFWwindow* window;
	VkInstance instance;

}App;

// 
bool check_extensions_supported() {
	uint32_t glfw_extension_count = 0;
	const char** glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);
	uint32_t extension_count = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, nullptr);
	std::vector<VkExtensionProperties> extensions(extension_count);
	vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, extensions.data());

	for (uint32_t i = 0; i < glfw_extension_count; ++i) {
		const char* req_ext = glfw_extensions[i];
		bool found = false;
		for (const auto& ext : extensions) {
			if (strcmp(req_ext, ext.extensionName) == 0) {
				found = true;
				break;
			}
		}
		if (!found) {
			std::cerr << "Required extension missing: " << req_ext << std::endl;
			return false;
		}
	}
	return true;
}




int main() {
	App app;
	assert(glfwInit() && "glfw initialisation failed\n" );
	printf("glfw initialized successfully\n");
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	app.window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
	assert(app.window && "window creation failed\n");
	printf("window created successfully\n");
	assert(check_extensions_supported() && "not all necessary glfw extensions are supported");
	printf("all necessary extensions are supported\n");
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	uint32_t instance_version = VK_API_VERSION_1_0;
	//vkEnumerateInstanceVersion(&instance_version);
	VkApplicationInfo app_info = {
		.sType                   = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pApplicationName        = "Hello Vulkan",
		.applicationVersion      = VK_MAKE_VERSION(1, 0, 0),
		.pEngineName             = "No Engine",
		.engineVersion           = VK_MAKE_VERSION(1, 0, 0),
		.apiVersion              = instance_version,
	};

	VkInstanceCreateInfo create_info = {
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pApplicationInfo        = &app_info,
		.enabledLayerCount       = 0,
		.enabledExtensionCount   = glfwExtensionCount,
		.ppEnabledExtensionNames = glfwExtensions,

	};
	VkResult result = vkCreateInstance(&create_info, nullptr, &app.instance);
	//assert(result && "instance creation failed\n");
	assert(result == VK_SUCCESS && "instance creation failed\n");
	printf("instance created successfully\n");
	while (!glfwWindowShouldClose(app.window)) {
		glfwPollEvents();
	}

	vkDestroyInstance(app.instance, nullptr);
	glfwDestroyWindow(app.window);


	glfwTerminate();
	return EXIT_SUCCESS;
}

