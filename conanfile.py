from conans import ConanFile, CMake, tools


class EnttpackmanConan(ConanFile):
    name = "entt-packman"
    version = "1.0.0"
    license = "MIT License"
    author = "Original author: Indi Kernick, CMake+Conan modificaitons: Pau Farre"
    url = "github.com/Hopobcn/entt-packman"
    description = "entt packman example"
    topics = ("game dev", "ecs", "entt", "packman")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = "shared=False"
    generators = "cmake"

    # requirements
    requires = ( "sdl2/2.0.9@bincrafters/stable" )
    build_requires = ( "cmake_installer/3.12.4@conan/stable" )

    def config_options(self):
        if self.settings.os == 'Windows':
            del self.options.fPIC

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        self.copy("*.h", dst="include", src="include")
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.lib", dst="bin", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)