include("../../libcogra/buildutils/CreateApp.cmake")
project(BasicImageProcessing)
set(ContribLibraries GLM COGRA STBIMAGE)
CreateApp(ContribLibraries)
