from conan import ConanFile
from conan.tools.files import copy


class GamutViewerRecipe(ConanFile):
    generators = 'CMakeDeps', 'CMakeToolchain'
    settings = 'os', 'compiler', 'build_type', 'arch'

    def requirements(self):
        self.requires('catch2/3.3.1')
        self.requires('glfw/3.3.8')
        self.requires('glm/cci.20230113')
        self.requires('imgui/cci.20230105+1.89.2.docking')
        self.requires('stb/cci.20220909')

    def generate(self):
        imgui = self.dependencies['imgui/cci.20230105+1.89.2.docking']
        self.output.info(f'{imgui.cpp_info}.')
        backends = ['imgui_impl_glfw.*',
                    'imgui_impl_opengl3.*',
                    'imgui_impl_opengl3_loader.*']
        for backend in backends:
            copy(self, backend, imgui.cpp_info.srcdirs[0], self.build_folder)
