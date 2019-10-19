#pragma once

#include "2d/geometry/point.h"
#include "2d/geometry/pixel.h"
#include "2d/barrel/lor.h"
#include "2d/barrel/square_detector.h"
#include "2d/barrel/ring_scanner.h"
#include "2d/barrel/generic_scanner.h"
#include "common/model.h"
#include "common/types.h"
#include "util/delegate.h"
#include "util/random.h"

namespace PET2D {
namespace Barrel {
/// CUDA optimized subimplementation
namespace GPU {

/// \cond PRIVATE

using Point = PET2D::Point<F>;
using Pixel = PET2D::Pixel<S>;
using LOR = Barrel::LOR<S>;
using Event = Barrel::Event<F>;
using SquareDetector = Barrel::SquareDetector<F>;
using Scanner = Barrel::GenericScanner<SquareDetector, S>;
using Model = Common::ScintillatorAccept<F>;

/// \endcond

namespace Matrix {

/// CUDA sink for unimplemented versions
template <class ScannerClass>
void run(ScannerClass& scanner,
         util::random::tausworthe& rng,
         int n_emissions,
         double tof_step,
         int n_tof_positions,
         int n_pixels,
         double s_pixel,
         double length_scale,
         util::delegate<void(int completed, bool finished)> progress,
         util::delegate<void(LOR lor, S position, Pixel pixel, Hit hits)> entry,
         int device,
         int n_blocks,
         int n_threads_per_block,
         util::delegate<void(const char* device_name, int n_emissions)> info) {
  // unused
  (void)scanner, (void)rng, (void)n_emissions, (void)tof_step,
      (void)n_tof_positions, (void)n_pixels, (void)s_pixel, (void)length_scale,
      (void)progress, (void)entry, (void)device, (void)n_blocks,
      (void)n_threads_per_block, (void)info;
  throw("GPU does not support this scanner type");
}

/// CUDA optimized Monte-Carlo implementation for square detector
template <>
void run<Scanner>(
    Scanner& scanner,
    util::random::tausworthe& rng,
    int n_emissions,
    double tof_step,
    int n_tof_positions,
    int n_pixels,
    double s_pixel,
    double length_scale,
    util::delegate<void(int completed, bool finished)> progress,
    util::delegate<void(LOR lor, S position, Pixel pixel, Hit hits)> entry,
    int device,
    int n_blocks,
    int n_threads_per_block,
    util::delegate<void(const char* device_name, int n_emissions)> info);

}  // Matrix
}  // GPU
}  // Barrel
}  // PET2D
