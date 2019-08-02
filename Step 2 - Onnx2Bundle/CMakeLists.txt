add_executable(OnnxBundleGenerator
  Loader.cpp
  OnnxBundleGenerator.cpp)

target_link_libraries(OnnxBundleGenerator
                      PRIVATE
                        Backends
                        Base
                        Converter
                        ExecutionEngine
                        HostManager
                        Graph
                        Importer
                        Optimizer
                        Quantization
                        LLVMSupport)
