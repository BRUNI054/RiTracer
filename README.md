## How to run the raytracer:
    Compile with standard flags in cmake, and navigate into the buildVCPkg/src folder and run main. Main takes argument of width, height, samples per pixel, recursion depth, and file name, in that order.
    
    So to generate the image with a width of 150, a height of 100, 4 samples per pixel, and a recursion depth of 3, named CoolPic.png you would run:

    ./main 150 100 4 3 CoolPic.png

    I reccomend prioritizing recursion depth over samples per pixel in terms of where you dedicate your somputing power, as the image looks cooler the deeper you go.

    To check shadows, as they aren't super prominent in the image generated in main, run the test_shadows executable , also located in buildVCPkg/src


## How to run the Rasterizer
    Compile with standard flags in in cmake, and navigate to the buildVCPkg/OpenGL directory. Move or copy the shaders (all of them) from the RiTracer/OpenGL directory to the RiTracer/buildVCPkg/OpenGL directory.To run a basic objloader, run objTest with the file you want to load as a parameter.

    So to run it with the file stanford_bunny.obj, you would run:

    ./objTest stanford_bunny.obj

    To see my cool dice roller, textures in progress, run ./D6. It'll generate a 6 sided color coded die on your screen, which should be without a background. It'll start on a roll, and you can reroll it by pressing the R key.

    For both of these scenes, the camera can be moved up, down, left, and right using W, A, S, D, and can be zoomed in and out using W and S while holding shift.