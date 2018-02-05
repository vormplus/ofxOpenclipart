# ofxOpenclipart

An add-on for openFrameworks that searches the [Openclipart](https://openclipart.org/) API for SVG files. The add-on also saves the SVG files you’ve searched for to the bin/data folder of your project so you won’t have to load them from the server every time you run your app. The screenshot below shows you the folder structure after running the example multiple times with different search keywords.

![Cached SVG files in the bin/data folder.](https://github.com/vormplus/ofxOpenclipart/blob/master/images/openclipart-folder-structure.png)

## Dependencies

This project uses [ofxJSON](https://github.com/jeffcrouse/ofxJSON) to parse the JSON data returned by the Openclipart API.

## How to use this add-on

Add the add-on to your project using the openFrameworks project generator. You will also need to add **ofxJSON** for this add-on to work, and **ofxSVG** to display the SVG files the API returns.

In your `ofApp.h` file, you need to define an ofxOpenclipart variable, so you can access all of its methods in your program.

	ofxOpenclipart openclipart;

In your `ofApp.cpp` file, you can call the `search()` method on the openclipart object. This method will return 10 SVG files matching this keyword, sorted by most downloaded.

	openclipart.search( “mushroom” );

If you want to download more items, you can change the defaults by calling the `setAmount()` method. You can search for up to 200 files, but note that this will take a while to load.

	penclipart.setAmount( 20 );

By default, the items are sorted by most downloaded. You can also change this by calling the `setSortMethod()` method. Possible values for this method are “**date**”, “**downloads**”, and “**favorites**”.

	openclipart.setSortMethod("favorites");

If you want to know when the add-on is finished loading new SVG files from the server, or those stored in the bin/data folder of your project, you can call the `isFinishedLoading()` method. You’ll usually use this one in the `update()` method of your `ofApp()` file.

	openclipart.isFinishedLoading()

And that’s it for this simple add-on.

## Example

The example included with this add-on will generate a collage based on the keyword you are searching for.

![A mushroom collage.](https://github.com/vormplus/ofxOpenclipart/blob/master/images/openclipart-mushroom-example.png)