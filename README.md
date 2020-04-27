# Imp
This is an engine for personal and educational purposes. 
The engine will be tested with the a game called BubbleBobble 
chosen by my educational institution HOWEST Digital Arts & Entertainment.

This engine will be using OpenGL as the base and will for now only support Windows 32-bit and 64-bit.

With this engine I'm taking another approach that I learned when following tutorials from The Cherno on youtube.
His 'Engine Series' is well explained and is structured so that it's never boring to watch.
This means that there is code in here that strongly resembles the code in The Cherno's engine series.
That said, I will only write code that I understand myself completely and could implement without copy pasting.

Normally I would've used a static library for this engine, but when I thought about the future and 
the possibility of coming across dynamically linked libraries. I thought it would be a good experience to make this engine
using dynamically linked libraries.

I had heard of CMake of teachers and had seen some files with cmake extensions but never knew what it actually was.
Though The Cherno is not using CMake, he's using something similar called Premake. He explained that he prefers using Premake
over CMake because Premake is easier to use and it uses lua to generate the project files.
I have only seen lua at for a few hours but using it with premake made me understand more
about what Premake and similar tools actually do, I think this is a nice experience for later.

So as you can see, The Cherno has a big influence in this project. That said, this assignment/personal project is supposed
to make my teachers and other people know what I can do. This means that I wouldn't prove what I can do 
if I only follow patterns and design choices that The Cherno has made in his engine series.
That is why I will mention which files/systems are strongly influenced by him. 

Events: The sort of event system that I would make before following the engine series, 
        would just be a command pattern with an observer pattern. 
        For the people who don't know what I'm talking about check this book out: 
        http://gameprogrammingpatterns.com/
        The Cherno implements this is kind of the same way but with callback functions and some cool macro's
        So callback functions and maybe macro's will be the things that i could add by learning from his engine series.
        
Entry point: This basically makes sure that the engine is in charge of the start of the application and controls the
             initialization of the system. 
             
The use of static functions: The Cherno uses static in ways that I didn't know were even possible. Like adding static function
                             implementations in derived classes or calling these from templated functions etc.

These are some links from The Cherno:

Social Media:
https://instagram.com/thecherno / https://thecherno.com/discord / https://twitter.com/thecherno

Youtube and GitHub:
https://www.youtube.com/channel/UCQ-W1KE9EYfdxhL6S4twUNw / https://github.com/TheCherno/Hazel
