
// public static method, that can be called from eval_q_t
double eval_q_u(double x, double y) const
{
  typedef DualNumber<Scalar, NumberArray<NDIM, Scalar> > FirstDerivType;
  typedef DualNumber<FirstDerivType, NumberArray<NDIM, FirstDerivType> > SecondDerivType;
  typedef SecondDerivType ADScalar;

  // Treat velocity as a vector
  NumberArray<NDIM, ADScalar> U;

  // Arbitrary manufactured solution
  U[0] = u_0 + u_x * std::cos(a_ux * PI * x / L) * u_y * std::cos(a_uy * PI * y / L);
  U[1] = v_0 + v_x * std::cos(a_vx * PI * x / L) * v_y * std::cos(a_vy * PI * y / L);
  ADScalar RHO = rho_0 + rho_x * std::cos(a_rhox * PI * x / L) * rho_y * std::cos(a_rhoy * PI * y / L);
  ADScalar P = p_0 + p_x * std::cos(a_px * PI * x / L) * p_y * std::cos(a_py * PI * y / L);

  // Temperature
  ADScalar T = P / RHO / R;

  // Perfect gas energies
  ADScalar E = 1./(Gamma-1.)*P/RHO;
  ADScalar ET = E + .5 * U.dot(U);

  // The shear strain tensor
  NumberArray<NDIM, typename ADScalar::derivatives_type> GradU = gradient(U);

  // The identity tensor I
  NumberArray<NDIM, NumberArray<NDIM, Scalar> > Identity = 
    NumberArray<NDIM, Scalar>::identity();

  // The shear stress tensor
  NumberArray<NDIM, NumberArray<NDIM, ADScalar> > Tau = mu * (GradU + transpose(GradU) - 2./3.*divergence(U)*Identity);

  // Temperature flux
  NumberArray<NDIM, ADScalar> q = -k * T.derivatives();

  // Euler equation residuals
  // Scalar Q_rho = raw_value(divergence(RHO*U));
  NumberArray<NDIM, Scalar> Q_rho_u = 
    raw_value(divergence(RHO*U.outerproduct(U) - Tau) + P.derivatives());

  return Q_rho_u[0];
}

// public, static method
double eval_q_v(double x, double y) const
{
  typedef DualNumber<Scalar, NumberArray<NDIM, Scalar> > FirstDerivType;
  typedef DualNumber<FirstDerivType, NumberArray<NDIM, FirstDerivType> > SecondDerivType;
  typedef SecondDerivType ADScalar;

  // Treat velocity as a vector
  NumberArray<NDIM, ADScalar> U;

  // Arbitrary manufactured solution
  U[0] = u_0 + u_x * std::cos(a_ux * PI * x / L) * u_y * std::cos(a_uy * PI * y / L);
  U[1] = v_0 + v_x * std::cos(a_vx * PI * x / L) * v_y * std::cos(a_vy * PI * y / L);
  ADScalar RHO = rho_0 + rho_x * std::cos(a_rhox * PI * x / L) * rho_y * std::cos(a_rhoy * PI * y / L);
  ADScalar P = p_0 + p_x * std::cos(a_px * PI * x / L) * p_y * std::cos(a_py * PI * y / L);

  // Temperature
  ADScalar T = P / RHO / R;

  // Perfect gas energies
  ADScalar E = 1./(Gamma-1.)*P/RHO;
  ADScalar ET = E + .5 * U.dot(U);

  // The shear strain tensor
  NumberArray<NDIM, typename ADScalar::derivatives_type> GradU = gradient(U);

  // The identity tensor I
  NumberArray<NDIM, NumberArray<NDIM, Scalar> > Identity = 
    NumberArray<NDIM, Scalar>::identity();

  // The shear stress tensor
  NumberArray<NDIM, NumberArray<NDIM, ADScalar> > Tau = mu * (GradU + transpose(GradU) - 2./3.*divergence(U)*Identity);

  // Temperature flux
  NumberArray<NDIM, ADScalar> q = -k * T.derivatives();

  // Euler equation residuals
  // Scalar Q_rho = raw_value(divergence(RHO*U));
  NumberArray<NDIM, Scalar> Q_rho_u = 
    raw_value(divergence(RHO*U.outerproduct(U) - Tau) + P.derivatives());

  return Q_rho_u[1];

}

// public, static method
double eval_q_e(double x, double y) const
{
  typedef DualNumber<Scalar, NumberArray<NDIM, Scalar> > FirstDerivType;
  typedef DualNumber<FirstDerivType, NumberArray<NDIM, FirstDerivType> > SecondDerivType;
  typedef SecondDerivType ADScalar;

  // Treat velocity as a vector
  NumberArray<NDIM, ADScalar> U;

  // Arbitrary manufactured solution
  U[0] = u_0 + u_x * std::cos(a_ux * PI * x / L) * u_y * std::cos(a_uy * PI * y / L);
  U[1] = v_0 + v_x * std::cos(a_vx * PI * x / L) * v_y * std::cos(a_vy * PI * y / L);
  ADScalar RHO = rho_0 + rho_x * std::cos(a_rhox * PI * x / L) * rho_y * std::cos(a_rhoy * PI * y / L);
  ADScalar P = p_0 + p_x * std::cos(a_px * PI * x / L) * p_y * std::cos(a_py * PI * y / L);

  // Temperature
  ADScalar T = P / RHO / R;

  // Perfect gas energies
  ADScalar E = 1./(Gamma-1.)*P/RHO;
  ADScalar ET = E + .5 * U.dot(U);

  // The shear strain tensor
  NumberArray<NDIM, typename ADScalar::derivatives_type> GradU = gradient(U);

  // The identity tensor I
  NumberArray<NDIM, NumberArray<NDIM, Scalar> > Identity = 
    NumberArray<NDIM, Scalar>::identity();

  // The shear stress tensor
  NumberArray<NDIM, NumberArray<NDIM, ADScalar> > Tau = mu * (GradU + transpose(GradU) - 2./3.*divergence(U)*Identity);

  // Temperature flux
  NumberArray<NDIM, ADScalar> q = -k * T.derivatives();

  // Euler equation residuals
  // Scalar Q_rho = raw_value(divergence(RHO*U));
  // NumberArray<NDIM, Scalar> Q_rho_u = 
  //   raw_value(divergence(RHO*U.outerproduct(U) - Tau) + P.derivatives());

  // energy equation
  Scalar Q_rho_e = raw_value(divergence((RHO*ET+P)*U + q - Tau.dot(U)));

  return Q_rho_e;
}

// public, static method
template <typename Scalar>
Scalar MASA::ad_cns_2d_crossterms<Scalar>::eval_q_rho(Scalar x1, Scalar y1) const
{
  typedef DualNumber<Scalar, NumberArray<NDIM, Scalar> > FirstDerivType;
  typedef DualNumber<FirstDerivType, NumberArray<NDIM, FirstDerivType> > SecondDerivType;
  typedef SecondDerivType ADScalar;

  const Scalar& x = x1;
  const Scalar& y = y1;

  // Treat velocity as a vector
  NumberArray<NDIM, ADScalar> U;

  // Arbitrary manufactured solution
  U[0] = u_0 + u_x * std::cos(a_ux * PI * x / L) * u_y * std::cos(a_uy * PI * y / L);
  U[1] = v_0 + v_x * std::cos(a_vx * PI * x / L) * v_y * std::cos(a_vy * PI * y / L);
  ADScalar RHO = rho_0 + rho_x * std::cos(a_rhox * PI * x / L) * rho_y * std::cos(a_rhoy * PI * y / L);

  Scalar Q_rho = raw_value(divergence(RHO*U));

  return Q_rho;
}
