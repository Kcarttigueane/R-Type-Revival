from conan import ConanFile


class RTypeConan(ConanFile):
    name = "R-Type"
    version = "1.0"
    description = "R-Type"
    generators = ("CMakeDeps", "CMakeToolchain")
    settings = "os", "compiler", "build_type", "arch"

    def requirement(self):
        self.requires("sfml/2.5.1@bincrafters/stable")
        self.requires("boost/1.69.0@conan/stable")

    def build_requirements(self):
        self.build_requires("cmake/[>=3.25]")

    def configure(self):
        self.options["sfml"].shared = True
        self.options["boost"].shared = True

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin")
        self.copy("*.dylib*", dst="bin", src="lib")
        self.copy("*.so*", dst="bin", src="lib")
        self.copy("*.dll", dst="bin", src="lib")
        self.copy("*.dylib*", dst="bin", src="lib")
        self.copy("*.so*", dst="bin", src="lib")
        self.copy("*.dll", dst="bin", src="lib")
        self.copy("*.dylib*", dst="bin", src="lib")
        self.copy("*.so*", dst="bin", src="lib")
        self.copy("*.dll", dst="bin", src="lib")
        self.copy("*.dylib*", dst="bin", src="lib")
        self.copy("*.so*", dst="bin", src="lib")

