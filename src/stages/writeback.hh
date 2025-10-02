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

#include "components/register_file.hh"
#include "pipeline_registers/execute_to_writeback.hh"
#include "components/hazard_checking_unit.hh"

#ifndef __WRITEBACK_STAGE__
#define __WRITEBACK_STAGE__

class Writeback
{
  private:
    // primary components to perform this stage
    RegisterFile *register_file;
    ExecuteToWriteback *input_reg;
    HazardCheckingUnit *hazard_checking_unit;
    int data_in;

    // TODO: your additional fields here!

  public:
    Writeback(RegisterFile *register_file,
              ExecuteToWriteback *execute_to_writeback_register)
      : register_file(register_file),
        input_reg(execute_to_writeback_register)
        // TODO: construct your additional fields here or in the function!
    {  };

    bool tick() {
        if (input_reg->use_imm) {
          data_in = input_reg->imm;
        } else{
          data_in = input_reg->alu_output;
        }
        register_file->setRegister(input_reg->destination, data_in);
        // TODO: your implementation here!

        return false;
    };
};

#endif // __WRITEBACK_STAGE__
