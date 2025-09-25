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

#include "components/instruction_memory.hh"
#include "components/decoder.hh"
#include "components/register_file.hh"
#include "components/alu.hh"

#include <string>

#ifndef __SINGLE_CYCLE__
#define __SINGLE_CYCLE__

class SingleCycleProcessor
{
  private:
    // declare our components
    InstructionMemory instruction_memory;
    Decoder decoder;
    RegisterFile register_file;
    ALU alu;
    // TODO: your additional fields here!
    int program_counter;
    string operation;
    int destination;
    int source_register1;
    int source_register2;
    int imm;
    // scons build/RISCV/gem5.debug -j8 -linker=gold

    // some stats for neat accounting
    int cycles_executed;

  public:
    SingleCycleProcessor(string program_filename)
      : instruction_memory(program_filename),
        decoder(),
        register_file(8),
        alu(),
        // TODO: any additional fields constructed here or in the function!
        cycles_executed(0),
        program_counter(0)
    {  };

    void dumpRegisters()
    {
        for (int i = 0; i < 8 /* num_registers */; i++) {
            cout << "r" << i << ":    " << register_file.getRegister(i);
            if (i % 2 == 0) {
                cout << "\t";
            } else {
                cout << "\n";
            }
        }
    };

    void executeProgram()
    {
         /* Main Execution Loop */
         while (true) {
            cycles_executed++;

            // TODO: your implementation here!

            // The 5 steps according to pdf:

            // 1. retrieve an instruction from instruction memory
              // InstructionMemory(string program_filename)
                // accessing instruction memory is as easy as receiving an
                // index (i.e., program counter) and accessing the vector!
                  // string getInstruction(int idx)
            
            string instruction = instruction_memory.getInstruction(program_counter);

            decoder.decode(instruction, operation, destination, source_register1, source_register2, imm);

            if (operation == "ldi"){
              register_file.setRegister(destination, imm);
            } else if (operation == "end") {
              break; // exit the while loop
            } else {
              int reg1 = register_file.getRegister(source_register1);
              int reg2 = register_file.getRegister(source_register2);

              alu.setInputs(operation, reg1, reg2);
              unsigned int alu_output = alu.execute();
              register_file.setRegister(destination, alu_output);
            }
            program_counter++;



            // 2. decode it into interpretable signals
              // void decode(string instruction, string &operation, int &destination, int &source_register1, int &source_register2, int &imm)
            // 3. send those signals to the appropriate execution components
              // For the register file:
                // RegisterFile(int 8 // numregisters)
                // reg1 = getRegister(int source_register1)
                // reg2 = getRegister(int source_register2)

              // For the ALU:
                // setInputs(string operation, unsigned int reg1, unsigned int reg2)
                // execute()
            // 4. update the processor state as appropriate
              // For the ALU: setRegister(int idx, unsigned int data_in)
            // 5. cleanly exit when the processor reaches the end of the program
        }

        // dump stats and registers!
        cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << endl;
        cout << " ~~~~~~ Final stats (single cycle) ~~~~~ " << endl;
        cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << endl;

        cout << "cycles run     :   " << cycles_executed << endl;

        cout << "\n\n ~~~ Register Dump ~~~ " << endl;
        dumpRegisters();
    };
};

#endif // __SINGLE_CYCLE__
