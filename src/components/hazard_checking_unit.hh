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
    std::vector<int> destinations_in_use;
    bool bubble;


  public:
    HazardCheckingUnit(DecodeToExecute *decode_to_execute_register,
                       ExecuteToWriteback *execute_to_writeback_register)
      : decode_to_execute_register(decode_to_execute_register),
        execute_to_writeback_register(execute_to_writeback_register),
        bubble(false)
    {  };

    bool operandDependence()
    {
        // TODO: your implementation here!


        // ldi r1, 3
        // ldi r0, 1
        // ldi r2, 17
        // mod r3, r2, r1
        // mul r2, r2, r0
        // sub r4, r1, r2
        // end




        // Check if there is a data hazard
          // Store destination of every instruction and get rid of it when writeback completes
          // If another instruction comes in and relies on the same register, then start a bubble.

          // Add new destination to list of destinations
          if (decode_to_execute_register->destination != 0) {
            auto old_dest = std::find(destinations_in_use.begin(), destinations_in_use.end(), decode_to_execute_register->destination);
            if (old_dest != destinations_in_use.end()) { // If the register destination is in use, then create a bubble.
              bubble = true;
              destinations_in_use.push_back(decode_to_execute_register->destination);
            } else{ // Otherwise, the register destination is not in use, then add it to the list without making a bubble.
              destinations_in_use.push_back(decode_to_execute_register->destination);
            }
          }



          // Once we write to a destination, get rid of it from list of destinations
          if (execute_to_writeback_register->destination != 0) { //
            auto index_location = std::find(destinations_in_use.begin(), destinations_in_use.end(), execute_to_writeback_register->destination);
            if (index_location != destinations_in_use.end()) { // This shoukld never be false.
                destinations_in_use.erase(index_location);
            } else {
              std::cerr << "Error: Destination not in list! This should never happen!\n";
            }
          }

        decode_to_execute_register->bubble = bubble;
        return bubble;
    };
};

#endif // __HAZARD_CHECKING_UNIT__
