// Author: Neeraj Sharma <neerajsharma.9@outlook.com>
// License MIT

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
            for (int i = 0; i < 2; ++i)
            {
                search.Search(out var searchResults, keyword);
                Console.WriteLine($"searchResults is Score: {searchResults.mScore}, Url: '{searchResults.mUrl}'");
                Console.WriteLine();
            }
        }
    }
}
