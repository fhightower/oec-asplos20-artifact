// test-energy-storage.cpp
// Energy storage class test file
//
// Copyright 2019 Bradley Denby
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not
// use this file except in compliance with the License. You may obtain a copy of
// the License at <http://www.apache.org/licenses/LICENSE-2.0>.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
// License for the specific language governing permissions and limitations under
// the License.

// Standard library
#include <cstddef>           // size_t

// satsim
#include <EnergyStorage.hpp> // EnergyStorage
#include <Logger.hpp>        // Logger

int main(int argc, char** argv) {
  satsim::Logger logger("s");
  satsim::EnergyStorage energyStorage(1.0034, &logger);
  satsim::EnergyStorage* esClone = energyStorage.clone();
  delete esClone;
  // Each iteration is 0.1 s
  for(size_t i=0; i<1200; i++) {
    if(i%10==0) {
      energyStorage.logMeasurement(
       "current-a",static_cast<double>(i)/10.0,energyStorage.getCurrent()
      );
    }
    if(i%600==0) {
      energyStorage.logEvent("minute",static_cast<double>(i)/10.0);
    }
    energyStorage.update(0.1);
  }
  logger.exportCsvs("../test");
  return 0;
}
