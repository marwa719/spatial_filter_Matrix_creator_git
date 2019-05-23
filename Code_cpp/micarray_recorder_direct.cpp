/*
 * Copyright 2017 <Admobilize>
 * All rights reserved.
 */

#include <gflags/gflags.h>
#include <wiringPi.h>
#include <armadillo>

#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <valarray>

#include "./lib/CTrait_mic.h"

#include "../cpp/driver/everloop.h"
#include "../cpp/driver/everloop_image.h"
#include "../cpp/driver/matrixio_bus.h"
#include "../cpp/driver/microphone_array.h"
#include "../cpp/driver/microphone_core.h"

using namespace arma;

DEFINE_int32(sampling_frequency, 16000, "Sampling Frequency");
DEFINE_int32(duration, 5, "Interrupt after N seconds");
DEFINE_int32(gain, -1, "Microphone Gain");

namespace hal = matrix_hal;


  hal::MatrixIOBus bus;
  
void allumage_led(vec angle){
    hal::EverloopImage image1d(bus.MatrixLeds());

    hal::Everloop everloop;

    everloop.Setup(&bus);
  for (hal::LedValue &led : image1d.leds) {
      led.red = 0;
      led.green = 0;
      led.blue = 0;
      led.white = 0;
    }
    
  int n_led = (int)floor((angle(1)*34/(2*3.14) + (34- 1*34/(2*3.14))))%34;
  if (angle(0) == 0){
    for (hal::LedValue &led : image1d.leds) {
      
      led.white = 100;
    }
    }
  if(angle(0) == 3.14/6){
    if(n_led ==0) image1d.leds[34].blue = 50;
    else image1d.leds[n_led-1].blue = 50;

    image1d.leds[n_led].blue = 100;
    image1d.leds[(n_led+1)%34].blue = 50;
  } 
  
  if(angle(0) == 3.14/3){
    if(n_led ==0) image1d.leds[34].green = 50;
    else image1d.leds[n_led-1].green = 50;

    image1d.leds[n_led].green = 100;
    image1d.leds[(n_led+1)%34].green = 50;
    
    
  } 
  
  
  if(angle(0) == 3.14/2){
    if(n_led ==0) image1d.leds[34].red = 50;
    else image1d.leds[n_led-1].red = 50;

    image1d.leds[n_led].red = 100;
    image1d.leds[(n_led+1)%34].red = 50;
  } 
    everloop.Write(&image1d);
 
  }
    


int main(int argc, char *agrv[]) {
  google::ParseCommandLineFlags(&argc, &agrv, true);


  if (!bus.Init()) return false;

  if (!bus.IsDirectBus()) {
    std::cerr << "Kernel Modules has been loaded. Use ALSA implementation "
              << std::endl;
    return false;
  }

  int sampling_rate = FLAGS_sampling_frequency;
  //int seconds_to_record = FLAGS_duration;

  // Microhone Array Configuration
  hal::MicrophoneArray mics;
  mics.Setup(&bus);
  mics.SetSamplingRate(sampling_rate);
  if (FLAGS_gain > 0) mics.SetGain(FLAGS_gain);

  mics.ShowConfiguration();


  // Microphone Core Init
  hal::MicrophoneCore mic_core(mics);
  mic_core.Setup(&bus);



  Mat<double> buffer =zeros( mics.NumberOfSamples(), mics.Channels()); 
 
     

      
    while(true){
       uint32_t samples = 0;

      mics.Read(); /* Reading 8-mics buffer from de FPGA */
      cout << "nbr d'ech" << 0.1*FLAGS_sampling_frequency << endl;
      /* buffering */
     
      for (uint32_t s = 0; s <mics.NumberOfSamples(); s++) {  
        
        for (uint16_t c = 0; c < mics.Channels(); c++) { /* mics.Channels()=7 */
          
          buffer(samples,c) = mics.At(s, c);
     
        
        }
        samples++;
      }
      
      
      CTrait_mic Tf;
      vec angle = Tf.traitement(buffer);
      
      
      allumage_led(angle);
      
      
      
 }

  return 0;
}
