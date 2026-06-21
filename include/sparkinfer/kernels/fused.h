#pragma once
#include <cuda_runtime.h>

namespace sparkinfer { namespace kernels {

// Fused RMSNorm:  out[r] = weight * x[r] / sqrt(mean(x[r]^2) + eps)
// Optionally adds a residual first (out and residual may alias x).
//   x / residual / out: [rows, cols] (bf16), weight: [cols] (bf16)
void launch_rmsnorm(const void* x_bf16, const void* weight_bf16, void* out_bf16,
                    int rows, int cols, float eps, cudaStream_t stream = nullptr);

void launch_add_rmsnorm(const void* x_bf16, const void* residual_bf16,
                        const void* weight_bf16, void* out_bf16,
                        int rows, int cols, float eps, cudaStream_t stream = nullptr);

}} // namespace sparkinfer::kernels
