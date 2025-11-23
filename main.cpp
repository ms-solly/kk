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
//skeleton functions
void init_window(App *app);
void create_instance(App *app);

void init_vulkan(App *app);
void main_loop(App *app);
void cleanup(App *app);

// resource functions
VkInstanceCreateInfo res_instance(App app);






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




VkInstanceCreateInfo res_instance(){
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	uint32_t instance_version = VK_API_VERSION_1_0;
	vkEnumerateInstanceVersion(&instance_version);
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
	return create_info;

}

void run(App *app) {
	init_window(app);
        init_vulkan(app);
        main_loop(app);
        cleanup(app);

}
void init_window(App *app){
	assert(glfwInit() && "glfw initialisation failed\n" );
	printf("glfw initialized successfully\n");
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	app->window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
	assert(app->window && "window creation failed\n");
	printf("window created successfully\n");
}
void create_instance(App *app){
	assert(check_extensions_supported() && "not all necessary glfw extensions are supported");
	printf("all necessary extensions are supported\n");
	VkInstanceCreateInfo create_info = res_instance();
	VkResult result = vkCreateInstance(&create_info, nullptr, &app->instance);
	//assert(result && "instance creation failed\n");
	assert(result == VK_SUCCESS && "instance creation failed\n");
	printf("instance created successfully\n");
}
void init_vulkan(App *app) {
	create_instance(app);
}

void main_loop(App *app) {
	while (!glfwWindowShouldClose(app->window)) {
		glfwPollEvents();
	}
}

void cleanup(App *app) {
	glfwDestroyWindow(app->window);


	glfwTerminate();
}

int main() {
	App app;

	try {
		run(&app);
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

