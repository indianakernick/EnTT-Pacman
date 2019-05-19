from conans import ConanFile, CMake, tools


class EnttpacmanConan(ConanFile):
    name = "entt-pacman"
    version = "1.0.0"
    license = "MIT License"
    author = "Indi Kernick"
    url = "https://github.com/Kerndog73/EnTT-Pacman"
    description = "entt pacman example"
    topics = ("game dev", "ecs", "entt", "pacman")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = "shared=False"
    generators = "cmake"

    # requirements
    requires = ( "entt/3.0.0@skypjack/stable", "sdl2/[>2.0.5 <2.1.0]@bincrafters/stable", "glm/0.9.9.4@g-truc/stable" )
    build_requires = ( "cmake_installer/3.12.4@conan/stable" )

    def config_options(self):
        if self.settings.os == 'Windows':
            del self.options.fPIC

    #configure
    #requirements
    #package_id
    #build_requirements
    #build_id
    #system_requirements
    #source
    #imports

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

    #deploy