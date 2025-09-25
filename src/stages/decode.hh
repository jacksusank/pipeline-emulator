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

#include "components/decoder.hh"
#include "components/register_file.hh"
#include "pipeline_registers/fetch_to_decode.hh"
#include "pipeline_registers/decode_to_execute.hh"

#ifndef __DECODE_STAGE__
#define __DECODE_STAGE__

class Decode
{
  private:
    // primary components to perform this stage
    Decoder *decoder;
    RegisterFile *register_file;
    FetchToDecode *input_reg;
    DecodeToExecute *output_reg;

    // TODO: your additional fields here!
    string operation;
    int destination;
    int source_register1;
    int source_register2;
    int imm;

  public:
    Decode(Decoder *decoder, RegisterFile *register_file,
           FetchToDecode *fetch_to_decode_register,
           DecodeToExecute *decode_to_execute_register)
      : decoder(decoder),
        register_file(register_file),
        input_reg(fetch_to_decode_register),
        output_reg(decode_to_execute_register)
        // TODO: construct your additional fields here or in the function!
    {  };

    bool tick()
    {
      // TODO: your implementation here!

      if (input_reg->instruction == ""){
        return false;
      }
      string instruction = input_reg->instruction;
      (*decoder).decode(instruction, operation, destination, source_register1, source_register2, imm);
      
      output_reg->operation = operation;
      output_reg->destination = destination;
      output_reg->register1_val = (*register_file).getRegister(source_register1);
      output_reg->register2_val = (*register_file).getRegister(source_register2);

      // output_reg->source_register1 = source_register1;
      // output_reg->source_register2 = source_register2;
      output_reg->imm = imm;

      if (operation == "end"){
        return true;
      } else{
        return false;
      }
    };
};

#endif // __DECODE_STAGE__
