//
// Created by famiglia on 16/01/21.
//

#ifndef SOURCE_FUTURAMA_H
#define SOURCE_FUTURAMA_H

#include <future>
#include <thread>
/*
 * A future is an object that can retrieve a value from some provider object or function,
 * properly synchronizing this access if in different threads.

    "Valid" futures are future objects associated to a shared state, and are constructed by calling one of the following functions:

    async
    promise::get_future
    packaged_task::get_future

 */

#include <vector>
using namespace std;

/*
vector<float> getSeismicSamples() { int i = 1;
    i++;
    return vector<float>();
}

// Computes the FFT (fast Fourier transform) of the passed samples. Takes 200ms
vector<float> computeFFT(const vector<float>& samples){ return vector<float>(); }
// Perfom time-domain filtering on seismic samples. Takes 600ms.
vector<float> timeDomainFilter(const vector<float>& samples){}
// Perfom frequency-domain filtering on seismic samples. Takes 500ms.
vector<float> frequencyDomainFilter(const vector<float>& samples){}
// Write samples to file. Takes 100ms.
void writeDataToFile(const vector<float>& filteredTimeDomainSamples,
                     const vector<float>& filteredFrequencyDomainSamples);


void filter(const vector<float>& in, vector<float>* out) { *out = timeDomainFilter(in); }

[[noreturn]] void readWithPlainThreads() {

    for (;;) {
        auto samples = getSeismicSamples();
        vector <float> timeFiltered;
        thread t1 (filter, samples, &timeFiltered); //600ms
        vector <float> freqFiltered = frequencyDomainFilter(computeFFT(samples));; //700ms
        t1.join();
        writeDataToFile(timeFiltered, freqFiltered);
    }
}

class Futurama {

    [[noreturn]] static void oldMain() {
        for(;;)
        {
            auto timeDomainSamples = getSeismicSamples();
            writeDataToFile(timeDomainFilter(timeDomainSamples),
                            frequencyDomainFilter(computeFFT(timeDomainSamples)));
        }
    }

    //compututation time:
    filter in time domain: 600ms
     * compute fft 200ms:
     * filter in freq domain: 500ms
     * write to file 100ms
     * this goes out of 1000ms due to the sequential operations filter in time and filter in frequency
     * I can run this two functions in parallel using this
     *
     * compute fft --- (tdf // fdf) -- write to file. this should take 200 + 600+100 < 1000ms and will remove the problem

    [[noreturn]] static void main() {
        for(;;)
        {
            auto timeDomainSamples = getSeismicSamples();


            //write to file should wait for time domain and filter domain filtering
            future<vector<float>> fut = async(launch::async, timeDomainFilter, timeDomainSamples);

            vector<float> timeDomainFilter = frequencyDomainFilter(computeFFT(timeDomainSamples));
            vector <float> frequencyDomainFilter = fut.get();
            writeDataToFile(timeDomainFilter, frequencyDomainFilter);
        }
    }


};

*/
#endif //SOURCE_FUTURAMA_H
