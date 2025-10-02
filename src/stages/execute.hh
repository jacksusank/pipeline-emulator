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
 * Contributor: Jack Susank
 */

#include "components/alu.hh"
#include "pipeline_registers/decode_to_execute.hh"
#include "pipeline_registers/execute_to_writeback.hh"

#ifndef __EXECUTE_STAGE__
#define __EXECUTE_STAGE__

class Execute
{
  private:
    // primary components to perform this stage
    ALU *alu;
    DecodeToExecute *input_reg;
    ExecuteToWriteback *output_reg;

    // TODO: your additional fields here!

  public:
    Execute(ALU *alu, DecodeToExecute *decode_to_execute_register,
            ExecuteToWriteback *execute_to_writeback_register)
      : alu(alu),
        input_reg(decode_to_execute_register),
        output_reg(execute_to_writeback_register)
        // TODO: construct your additional fields here or in the function!
    {  };


    bool tick()
    {
      // TODO: your implementation here!
      string operation = input_reg->operation;
      int destination = input_reg->destination;
      int register1_val = input_reg->register1_val;
      int register2_val = input_reg->register2_val;
      int imm = input_reg->imm;

      if (operation == "ldi"){
        // register_file.setRegister(destination, imm);
        output_reg->destination = destination;
        output_reg->imm = imm;
        output_reg->alu_output = 0;
        output_reg->use_imm = true;

      } else if (operation == "end") {
        // break; // exit the while loop
        return true;
      } else {
        (*alu).setInputs(operation, register1_val, register2_val);
        unsigned int alu_output = (*alu).execute();
        // register_file.setRegister(destination, alu_output);
        output_reg->destination = destination;
        output_reg->imm = 0;
        output_reg->alu_output = alu_output;
        output_reg->use_imm = false;

      }
      return false;
    };
};

#endif // __EXECUTE_STAGE__
