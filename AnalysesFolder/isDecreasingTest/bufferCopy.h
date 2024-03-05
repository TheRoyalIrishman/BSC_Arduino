/*
 * bufferCopy.h
 *
 *  Created on: Mar 4, 2024
 *      Author: sethm
 */

#ifndef BUFFERCOPY_H_
#define BUFFERCOPY_H_


#pragma once

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 20
#endif

#ifndef INFINITY
#define HUGE_ENOUGH 1e300
#define INFINITY ((HUGE_ENOUGH)*(HUGE_ENOUGH))
#endif

class Buffer {
public:
  constexpr Buffer() noexcept : m_data{0}, m_lastIndex(0) {}

  void addPoint(float value) noexcept {
    m_data[m_lastIndex] = value;
    m_lastIndex = (m_lastIndex + 1) % BUFFER_SIZE;
  }

  bool isDecreasing() const noexcept {
    int firstIndex = (m_lastIndex + 1) % BUFFER_SIZE;
    int prevIndex = firstIndex;
    int decCount = 0;
    for (int i = 1; i < BUFFER_SIZE; ++i) {
      int nextIndex = (firstIndex + i) % BUFFER_SIZE;
      if (m_data[prevIndex] > m_data[nextIndex]) {
        ++decCount;
      }
      prevIndex = nextIndex;
    }
    return decCount > BUFFER_SIZE*0.4;
  }
  float maximum() const noexcept {
    float currMax = -INFINITY;
    for (int i = 0; i < BUFFER_SIZE; ++i) {
      if (m_data[i] > currMax) {
        currMax = m_data[i];
      }
    }
    return currMax;
  }

  float minimum() const noexcept {
    float currMin = INFINITY;
    for (int i = 0; i < BUFFER_SIZE; ++i) {
      if (m_data[i] < currMin) {
        currMin = m_data[i];
      }
    }
    return currMin;
  }

private:
  float m_data[BUFFER_SIZE];
  int m_lastIndex;
};



#endif /* BUFFERCOPY_H_ */
