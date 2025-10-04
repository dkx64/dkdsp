#include "RingBuf.hh"
#include <cstddef>

namespace dkdsp {
    class Delay {
    public:
        Delay() {}
        void reinit (int channels, int sample_rate) {
            delay_lines.erase(delay_lines.begin(),delay_lines.end());
            project_sample_rate = sample_rate;
            for (int i = 0; i < channels; ++i ) {
                delay_lines.push_back(DRingBuf<float>(sample_rate*10));
                delay_lines[i].push(0.0);
            }
        }
        size_t delay_time(int delay_param, bool is_timed, size_t sample_rate, float tempo) {
            float sss = (60/tempo)*sample_rate;
            switch (is_timed) {
                case true: switch (delay_param) {
                    case 1: return sss/8;
                    case 2: return sss/4;
                    case 3: return sss/2;
                    case 4: return sss;
                    case 5: return sss*1.;
                    case 6: return sss*1.5;
                    case 7: return sss*1.75;
                    case 8: return sss*2.0;
                    default: return 8100;
                }
                case false: switch (delay_param) {
                    case 1: return sample_rate/10;
                    case 2: return sample_rate/5;
                    case 3: return sample_rate/2;
                    case 4: return sample_rate;
                    case 5: return sample_rate*1.25;
                    case 6: return sample_rate*1.5;
                    case 7: return sample_rate*1.75;
                    case 8: return sample_rate*2.0;
                    default: return sample_rate;
                }
            }
        }
        float process_sample (float sample, float feedback, int channel, int delay_param, int tempo, bool timed) {
            float output_sample = 0.0;
            if (delay_lines[channel].is_full()) {
                delay_lines[channel].pop();
            }
            output_sample = feedback * delay_lines[channel].get(delay_lines[channel].size() - delay_time(delay_param, timed, project_sample_rate, tempo));

            delay_lines[channel].push(sample + output_sample);
            return output_sample;
        }
    private:
        std::vector<DRingBuf<float>> delay_lines;
        int project_sample_rate;
    };
}
