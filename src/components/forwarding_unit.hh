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

#include "pipeline_registers/decode_to_execute.hh"
#include "pipeline_registers/execute_to_writeback.hh"

#ifndef __FORWARDING_UNIT__
#define __FORWARDING_UNIT__

class ForwardingUnit
{
  private:
    DecodeToExecute *decode_to_execute_register;
    ExecuteToWriteback *execute_to_writeback_register;
    bool bubble;
    int last_destination_register;
    int reg1;
    int reg2;
    string this_operation;

  public:
    ForwardingUnit(DecodeToExecute *decode_to_execute_register,
                   ExecuteToWriteback *execute_to_writeback_register)
      : decode_to_execute_register(decode_to_execute_register),
        execute_to_writeback_register(execute_to_writeback_register),
        bubble(false),
        last_destination_register(0),
        reg1(0),
        reg2(0),
        this_operation("")
    {  };

bool operandDependence()
    {
      if (bubble) {
        last_destination_register = 0;
      } else {
        last_destination_register = execute_to_writeback_register->destination;
      }
      reg1 = decode_to_execute_register->source_register1;
      reg2 = decode_to_execute_register->source_register2;
      this_operation = decode_to_execute_register->operation;


      if (last_destination_register != 0) {
        if (last_destination_register == reg1) {
          if (execute_to_writeback_register->use_imm) {
            bubble = true;            

          } else{
            decode_to_execute_register->register1_val = execute_to_writeback_register->alu_output;
            bubble = false;            

          }
        } else if (last_destination_register == reg2){
          if (execute_to_writeback_register->use_imm) {
            decode_to_execute_register->register2_val = execute_to_writeback_register->imm;
            bubble = false;
          } else {
            decode_to_execute_register->register2_val = execute_to_writeback_register->alu_output;
            bubble = false;
          }
        } else {
          bubble = false;
        }
      } else {
        bubble = false;
      }    
      return bubble;
    };
};


#endif // __FORWARDING_UNIT__
