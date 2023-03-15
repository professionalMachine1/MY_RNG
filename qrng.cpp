#include <iostream>
#include <iomanip>
#include <Rcpp.h>

typedef double float_type;

class qrng
{
private:
  size_t cur_num;
  float_type alpha, alpha2, h1, h2, h3, int_val;
public:
  qrng();
  qrng(size_t seed);
  float_type next();
};

qrng::qrng()
{
  float_type seed = static_cast<float_type>(time(NULL));
  alpha = 2 * asin(1) - 3;
  alpha += seed / (seed + 52511);
  // ---
  h1 = log(2.0);
  h2 = log10(3);
  h3 = exp(1) - 2;
  
  alpha2 = pow(alpha, 1.5);
  // ---
  cur_num = 1;
  int_val = 0;
}

qrng::qrng(size_t seed_)
{
  float_type seed = static_cast<float_type>(seed_);
  alpha = 2 * asin(1) - 3;
  alpha += seed / (seed + 119312);
  // ---
  h1 = log(2.0); 
  h2 = log10(3); 
  h3 = exp(1) - 2;
  alpha2 = pow(alpha, 2);
  // ---
  cur_num = 1;
  int_val = 0;
}

float_type qrng::next()
{
  float_type res;
  res = modf(cur_num * (h1 * alpha2 + h2 * alpha + h3), &int_val);
  
  h1 = modf(cur_num * (h1 * alpha + h2) + int_val, &int_val);
  h2 = modf(cur_num * (h2 * res + h1) + int_val, &int_val);
  h3 = modf(cur_num * (h3 * alpha2 + h2) + int_val, &int_val);
  
  if (++cur_num > 10000)
    cur_num = 1;
  
  return res;
}

qrng rng;

// [[Rcpp::export]]
void initialize_rng(size_t seed = 0)
{
  if (seed != 0)
    rng = qrng(seed);
}

// [[Rcpp::export]]
Rcpp::NumericVector generate_rn(size_t N)
{
  Rcpp::NumericVector x(N);
  for (size_t i = 0; i < N; ++i) {
    x[i] = rng.next();
  }
  
  return x;
}

