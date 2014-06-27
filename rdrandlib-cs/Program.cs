//------------------------------------------------------------------------------------
// Copyright (c) 2014 Dilshan R Jayakody. [jayakody2000lk@gmail.com]
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//------------------------------------------------------------------------------------

using System;
using System.Runtime.InteropServices;

namespace rdrandlib_cs
{
    class Program
    {
        static void Main(string[] args)
        {
          const int randomNumberCount = 20;  
	        IntPtr randomBuffer;
	        byte randomResult;
          int[] randomBufferArray = new int[randomNumberCount];

            randomBuffer = Marshal.AllocHGlobal(sizeof(uint) * randomNumberCount);
            randomResult = rdrandlib.GenerateRandomSet(randomNumberCount, randomBuffer);

            if(randomResult == rdrandlib.RDRAND_SUPPORT)
            {
                Console.WriteLine("RDRAND support is available.");
                Marshal.Copy(randomBuffer, randomBufferArray, 0, randomBufferArray.Length);

                for (int scanPos = 0; scanPos < randomNumberCount; scanPos++)
                {
                    Console.WriteLine(" " + (uint)randomBufferArray[scanPos]);
                }
            }
            else
            {
                Console.WriteLine("RDRAND support is not available.");
            }

            Marshal.FreeHGlobal(randomBuffer);
            Console.WriteLine("\nPress <ENTER> to close this application...");
            Console.ReadKey();
        }
    }
}
