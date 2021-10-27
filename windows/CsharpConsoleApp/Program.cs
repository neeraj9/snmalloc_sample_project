using System;
using DotNETCppInteropLibrary;

namespace CsharpConsoleApp
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("---------------------------------");
            Console.WriteLine(".NET / C++ Sample App to test");
            Console.WriteLine("custom C++ memory allocator");
            Console.WriteLine("---------------------------------");

            InteropSearchWeb search = new InteropSearchWeb();
            String keyword = "hello";
            InteropSearchResults searchResults = new InteropSearchResults(-1, "");
            for (int i = 0; i < 2; ++i)
            {
                search.Search(ref searchResults, keyword);
                Console.WriteLine($"searchResults is Score: {searchResults.mScore}, Url: '{searchResults.mUrl}'");
                Console.WriteLine();
            }
        }
    }
}
