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

#include "pipeline_registers/decode_to_execute.hh"
#include "pipeline_registers/execute_to_writeback.hh"
#include <iostream>
#include <vector> 
#include <algorithm> 

#ifndef __HAZARD_CHECKING_UNIT__
#define __HAZARD_CHECKING_UNIT__

class HazardCheckingUnit
{
  private:
    DecodeToExecute *decode_to_execute_register;
    ExecuteToWriteback *execute_to_writeback_register;
    bool bubble;
    int last_destination_register;
    int reg1;
    int reg2;


  public:
    HazardCheckingUnit(DecodeToExecute *decode_to_execute_register,
                       ExecuteToWriteback *execute_to_writeback_register)
      : decode_to_execute_register(decode_to_execute_register),
        execute_to_writeback_register(execute_to_writeback_register),
        last_destination_register(0),
        reg1(0),
        reg2(0)
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

      if (last_destination_register != 0){
        if ((last_destination_register == reg1) || (last_destination_register == reg2)){ // Data hazard!
          bubble = true;
        } else {
          bubble = false;
        }
      } else {
        bubble = false;
      }    
      return bubble;
    };
};

#endif // __HAZARD_CHECKING_UNIT__
