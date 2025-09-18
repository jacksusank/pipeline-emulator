/**
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * “AS IS” AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Copyright (c) 2025: ST, Pomona College.
 * Contributor: Your name here!
 */

#include <string>

#include "util.hh"

#ifndef __DECODER__
#define __DECODER__

using namespace std;

class Decoder
{

  public:
    Decoder()
    {  };

    // this function is the main execution function
    // because it would need to return several things as output,
    // it takes the values to return as references from the caller
    // so that the caller can appropriately manage handle it
    void decode(string instruction, string &operation, int &destination,
                int &source_register1, int &source_register2, int &imm)
    {
      source_register1 = 0;
      source_register2 = 0;

      operation = instruction.substr(0, 3);

      if (operation == "ldi") {
        destination = stoi(instruction.substr(5, 1));
        imm = stoi(instruction.substr(8, instruction.npos));
      } else if (operation == "end") {
        destination = 0;
        imm = 0;
      } else {
        destination = stoi(instruction.substr(5, 1));
        source_register1 = stoi(instruction.substr(9, 1));
        source_register2 = stoi(instruction.substr(13, 1));
      }
    };
};

#endif // __DECODER__
