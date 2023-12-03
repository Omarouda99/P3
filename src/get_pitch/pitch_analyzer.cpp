/// @file

#include <iostream>
#include <math.h>
#include "pitch_analyzer.h"

using namespace std;

/// Name space of UPC
namespace upc
{
  void PitchAnalyzer::autocorrelation(const vector<float> &x, vector<float> &r) const
  {

    for (unsigned int l = 0; l < r.size(); ++l)
    {
      /// \TODO Compute the autocorrelation r[l]
      /// \DONE Autocorrelation completed
      r[l] = 0;
      for (unsigned int n = 0; n < x.size() - l; ++n)
      {
        r[l] += x[n] * x[n + l];
      }
      r[l] /= x.size();
    }

    if (r[0] == 0.0F) //to avoid log() and divide zero
      r[0] = 1e-10;
  }

  void PitchAnalyzer::set_window(Window win_type)
  {
    if (frameLen == 0)
      return;

    window.resize(frameLen);
    const float c0 = 0.5435;
    const float c1 = 1 - c0;
    switch (win_type)
    {
    case HAMMING:
      /// \TODO Implement the Hamming window
      /// \DONE
      for (unsigned int i = 0; i < frameLen; i++)
      {
        window[i] = c0 - c1 * cos((2 * M_PI * i) / (frameLen - 1));
      }
      /// \DONE
      break;
    case RECT:
    default:
      window.assign(frameLen, 1);
    }
  }

  void PitchAnalyzer::set_f0_range(float min_F0, float max_F0)
  {
    npitch_min = (unsigned int)samplingFreq / max_F0;
    if (npitch_min < 2)
      npitch_min = 2; 

    npitch_max = 1 + (unsigned int)samplingFreq / min_F0;

    if (npitch_max > frameLen / 2)
      npitch_max = frameLen / 2;
  }

  bool PitchAnalyzer::unvoiced(float pot, float r1norm, float rmaxnorm) const
  {
    /// \TODO Implement a rule to decide whether the sound is voiced or not.
    /// * You can use the standard features (pot, r1norm, rmaxnorm),
    ///   or compute and use other ones.
    /// \DONE
    float score = 0;
    static float power_first_window = 0;
    static int window = 0;
    const float potvalue = potvalue_th, r1value = r1norm_th, rmaxvalue = rmaxnorm_th;

    if (pot < potvalue)
      score += 0.5;
    else if (r1norm < r1value)
      score += 0.5;
    else if (rmaxnorm < rmaxvalue)
      score += 0.5;
    if (score >= 0.5)
      return true;
    else
      return false;
  }

  float PitchAnalyzer::compute_pitch(vector<float> &x) const
  {
    if (x.size() != frameLen)
      return -1.0F;

    //Window input frame
    for (unsigned int i = 0; i < x.size(); ++i)
      x[i] *= window[i];

    vector<float> r(npitch_max);
    autocorrelation(x, r);

    vector<float>::const_iterator iRMax = r.begin() + npitch_min;

    /// \TODO
    /// Find the lag of the maximum value of the autocorrelation away from the origin.<br>
    /// Choices to set the minimum value of the lag are:
    ///    - The first negative value of the autocorrelation.
    ///    - The lag corresponding to the maximum value of the pitch.
    ///	   .
    /// In either case, the lag should not exceed that of the minimum value of the pitch.
    /// \DONE

    for (vector<float>::const_iterator iR = iRMax; iR < r.end(); iR++)
    {
      if (*iR > *iRMax)
      {
        iRMax = iR;
      }
    }
    unsigned int lag = iRMax - r.begin();

    float pot = 10 * log10(r[0]);
    
#if 1
    if (r[0] > 0.0F)
      cout << pot << '\t' << r[1] / r[0] << '\t' << r[lag] / r[0] << endl;
#endif

    if (unvoiced(pot, r[1] / r[0], r[lag] / r[0]))
      return 0;
    else
      return (float)samplingFreq / (float)lag;
  }
}