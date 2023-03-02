library(Rcpp);

sourceCpp("qrng.cpp");

N = 100000;
x <- generate_rn(N);
plot(x[1:N-1], x[2:N]);
hist(x, 15);

ks.test(x, punif)

N = N - 1;
x_3d <- data.frame(x1 = x[seq(1, N, 3)], 
                   x2 = x[seq(2, N, 3)], 
                   x3 = x[seq(3, N, 3)])
x_t3 <- table(lapply(x_3d, cut, br = seq(0,1,0.25)))
chisq.test(as.vector(x_t3))
