// emulate functions as macros for speed, they aren't inlined for some stupid reason
// see numerics.c for details
#if(TVDLF==0)

#if( (POSTPROC==1)||(LINEARINTERP==2) ) // use best for pp
#define z2e_1(f,k,j,i) (0.5*(dx[1][1][i]*f[k][j][im1mac(i)]+dx[1][1][im1mac(i)]*f[k][j][i])*ODX(2,1,i))
#define z2e_2(f,k,j,i) (0.5*(dx[1][2][j]*f[k][jm1mac(j)][i]+dx[1][2][jm1mac(j)]*f[k][j][i])*ODX(2,2,j))
#define z2e_3(f,k,j,i) (0.5*(dx[1][3][k]*f[km1mac(k)][j][i]+dx[1][3][km1mac(k)]*f[k][j][i])*ODX(2,3,k))
#define e2z_1(f,k,j,i) (0.5*(f[k][j][i] + f[k][j][ip1mac(i)]))
#define e2z_2(f,k,j,i) (0.5*(f[k][j][i] + f[k][jp1mac(j)][i]))
#define e2z_3(f,k,j,i) (0.5*(f[k][j][i] + f[kp1mac(k)][j][i]))
#define v2tov1(f,k,j,i) (0.25* ((f[k][j][i] + f[k][jp1mac(j)][i])*dx[1][1][im1mac(i)] + (f[k][j][im1mac(i)] + f[k][jp1mac(j)][im1mac(i)])* dx[1][1][i])*(ODX(2,1,i)))
#define v1tov2(f,k,j,i) (0.25* ((f[k][j][i] + f[k][j][ip1mac(i)])* dx[1][2][jm1mac(j)] + (f[k][jm1mac(j)][i] + f[k][jm1mac(j)][ip1mac(i)])* dx[1][2][j])*ODX(2,2,j))
#define z2c_3(f,k,j,i) (0.25*((f[k][j][i]*dx[1][1][im1mac(i)] + f[k][j][im1mac(i)]*dx[1][1][i])*dx[1][2][jm1mac(j)] + (f[k][jm1mac(j)][i]*dx[1][1][im1mac(i)] + f[k][jm1mac(j)][im1mac(i)]*dx[1][1][i])*dx[1][2][j])*ODX(2,1,i)*ODX(2,2,j))
#define c2z_3(f,k,j,i) (0.25*(f[k][j][i] + f[k][j][ip1mac(i)] + f[k][jp1mac(j)][i] + f[k][jp1mac(j)][ip1mac(i)]))

#define v2to050(f,k,j,i) (ODX(2,1,i)*ODX(2,3,k)*(0.125*(dx[1][3][k]*(dx[1][1][i]*(f[km1mac(k)][j][im1mac(i)] + f[km1mac(k)][jp1mac(j)][im1mac(i)]) + dx[1][1][im1mac(i)]*(f[km1mac(k)][j][i] + f[km1mac(k)][jp1mac(j)][i])) +dx[1][3][km1mac(k)]*(dx[1][1][i]*(f[k][j][im1mac(i)] + f[k][jp1mac(j)][im1mac(i)]) + dx[1][1][im1mac(i)]*(f[k][j][i] + f[k][jp1mac(j)][i])))) )

#define v3to005(f,k,j,i) (ODX(2,1,i)*ODX(2,2,j)*(0.125*(dx[1][2][j]*(dx[1][1][i]*(f[k][jm1mac(j)][im1mac(i)] + f[kp1mac(k)][jm1mac(j)][im1mac(i)]) + dx[1][1][im1mac(i)]*(f[k][jm1mac(j)][i] + f[kp1mac(k)][jm1mac(j)][i])) + dx[1][2][jm1mac(j)]*(dx[1][1][i]*(f[k][j][im1mac(i)] + f[kp1mac(k)][j][im1mac(i)]) + dx[1][1][im1mac(i)]*(f[k][j][i] + f[kp1mac(k)][j][i])))) )

#define v1to500(f,k,j,i) (ODX(2,2,j)*ODX(2,3,k)*(0.125*(dx[1][3][k]*(dx[1][2][j]*(f[km1mac(k)][jm1mac(j)][i] + f[km1mac(k)][jm1mac(j)][ip1mac(i)]) + dx[1][2][jm1mac(j)]*(f[km1mac(k)][j][i] + f[km1mac(k)][j][ip1mac(i)])) + dx[1][3][km1mac(k)]*(dx[1][2][j]*(f[k][jm1mac(j)][i] + f[k][jm1mac(j)][ip1mac(i)]) + dx[1][2][jm1mac(j)]*(f[k][j][i] + f[k][j][ip1mac(i)])))) )

#define v3tov1(f,k,j,i) (0.25*(dx[1][1][i]*(f[k][j][im1mac(i)] + f[kp1mac(k)][j][im1mac(i)]) + dx[1][1][im1mac(i)]*(f[k][j][i] + f[kp1mac(k)][j][i]))*ODX(2,1,i) )

#define v3tov2(f,k,j,i) (0.25*(dx[1][2][j]*(f[k][jm1mac(j)][i] + f[kp1mac(k)][jm1mac(j)][i]) + dx[1][2][jm1mac(j)]*(f[k][j][i] + f[kp1mac(k)][j][i]))*ODX(2,2,j) )

#define v1tov3(f,k,j,i) (0.25*(dx[1][3][k]*(f[km1mac(k)][j][i] + f[km1mac(k)][j][ip1mac(i)]) + dx[1][3][km1mac(k)]*(f[k][j][i] + f[k][j][ip1mac(i)]))*ODX(2,3,k) )

#define v2tov3(f,k,j,i) (0.25*(dx[1][3][k]*(f[km1mac(k)][j][i] + f[km1mac(k)][jp1mac(j)][i]) + dx[1][3][km1mac(k)]*(f[k][j][i] + f[k][jp1mac(j)][i]))*ODX(2,3,k))

#define c2z_3d(f,k,j,i) (0.125*(f[k][j][i] + f[k][j][ip1mac(i)] + f[k][jp1mac(j)][i] + f[k][jp1mac(j)][ip1mac(i)] + f[kp1mac(k)][j][i] + f[kp1mac(k)][j][ip1mac(i)] + f[kp1mac(k)][jp1mac(j)][i] + f[kp1mac(k)][jp1mac(j)][ip1mac(i)]))

#define z2c_3d(f,k,j,i) (ODX(2,1,i)*ODX(2,2,j)*(0.125*(dx[1][2][j]*(dx[1][1][i]*(f[k][jm1mac(j)][im1mac(i)] + f[kp1mac(k)][jm1mac(j)][im1mac(i)]) + dx[1][1][im1mac(i)]*(f[k][jm1mac(j)][i] + f[kp1mac(k)][jm1mac(j)][i])) + dx[1][2][jm1mac(j)]*(dx[1][1][i]*(f[k][j][im1mac(i)] + f[kp1mac(k)][j][im1mac(i)]) + dx[1][1][im1mac(i)]*(f[k][j][i] + f[kp1mac(k)][j][i])))) )

#define z2c_2(f,k,j,i) (ODX(2,1,i)*ODX(2,3,k)*(0.25*(dx[1][3][k]*(dx[1][1][i]*f[km1mac(k)][j][im1mac(i)] + dx[1][1][im1mac(i)]*f[km1mac(k)][j][i]) + dx[1][3][km1mac(k)]*(dx[1][1][i]*f[k][j][im1mac(i)] + dx[1][1][im1mac(i)]*f[k][j][i])) ))


#define c2z_2(f,k,j,i) (0.25*(f[k][j][i] + f[k][j][ip1mac(i)] + f[kp1mac(k)][j][i] + f[kp1mac(k)][j][ip1mac(i)]))

#define z2c_1(f,k,j,i) (0.25*(dx[1][3][k]*(dx[1][2][j]*f[km1mac(k)][jm1mac(j)][i] + dx[1][2][jm1mac(j)]*f[km1mac(k)][j][i]) + dx[1][3][km1mac(k)]*(dx[1][2][j]*f[k][jm1mac(j)][i] + dx[1][2][jm1mac(j)]*f[k][j][i]))*ODX(2,2,j)*ODX(2,3,k) )

#define c2z_1(f,k,j,i) (0.25*(f[k][j][i] + f[k][jp1mac(j)][i] + f[kp1mac(k)][j][i] + f[kp1mac(k)][jp1mac(j)][i]) )

#elif(LINEARINTERP==1)

#define z2e_1(f,k,j,i) (0.5*(f[k][j][im1mac(i)]+f[k][j][i]))
#define z2e_2(f,k,j,i) (0.5*(f[k][jm1mac(j)][i]+f[k][j][i]))
#define z2e_3(f,k,j,i) (0.5*(f[km1mac(k)][j][i]+f[k][j][i]))
#define e2z_1(f,k,j,i) (0.5*(f[k][j][i] + f[k][j][ip1mac(i)]))
#define e2z_2(f,k,j,i) (0.5*(f[k][j][i] + f[k][jp1mac(j)][i]))
#define e2z_3(f,k,j,i) (0.5*(f[k][j][i] + f[kp1mac(k)][j][i]))
#define v2tov1(f,k,j,i) (0.25* (f[k][j][i] + f[k][jp1mac(j)][i] + f[k][j][im1mac(i)] + f[k][jp1mac(j)][im1mac(i)] ))
#define v1tov2(f,k,j,i) (0.25* (f[k][j][i] + f[k][j][ip1mac(i)] + f[k][jm1mac(j)][i] + f[k][jm1mac(j)][ip1mac(i)] ))
#define z2c_3(f,k,j,i) (0.25*(f[k][j][i] + f[k][j][im1mac(i)] + f[k][jm1mac(j)][i]+ f[k][jm1mac(j)][im1mac(i)] ))
#define c2z_3(f,k,j,i) (0.25*(f[k][j][i] + f[k][j][ip1mac(i)] + f[k][jp1mac(j)][i] + f[k][jp1mac(j)][ip1mac(i)]))



#define v2to050(f,k,j,i) (0.125*(f[km1mac(k)][j][im1mac(i)] + f[km1mac(k)][j][i] + f[km1mac(k)][jp1mac(j)][im1mac(i)] + f[km1mac(k)][jp1mac(j)][i] + f[k][j][im1mac(i)] + f[k][j][i] + f[k][jp1mac(j)][im1mac(i)] + f[k][jp1mac(j)][i]) )

#define v3to005(f,k,j,i) (0.125*(f[k][jm1mac(j)][im1mac(i)] + f[k][jm1mac(j)][i] + f[k][j][im1mac(i)] + f[k][j][i] + f[kp1mac(k)][jm1mac(j)][im1mac(i)] + f[kp1mac(k)][jm1mac(j)][i] + f[kp1mac(k)][j][im1mac(i)] + f[kp1mac(k)][j][i]) )

#define v1to500(f,k,j,i) (0.125*(f[km1mac(k)][jm1mac(j)][i] + f[km1mac(k)][jm1mac(j)][ip1mac(i)] + f[km1mac(k)][j][i] + f[km1mac(k)][j][ip1mac(i)] + f[k][jm1mac(j)][i] + f[k][jm1mac(j)][ip1mac(i)] + f[k][j][i] + f[k][j][ip1mac(i)]) )

#define v3tov1(f,k,j,i) (0.25*(f[k][j][im1mac(i)] + f[k][j][i] + f[kp1mac(k)][j][im1mac(i)] + f[kp1mac(k)][j][i]) )

#define v3tov2(f,k,j,i) (0.25*(f[k][jm1mac(j)][i] + f[k][j][i] + f[kp1mac(k)][jm1mac(j)][i] + f[kp1mac(k)][j][i]) )


#define v1tov3(f,k,j,i) (0.25*(f[km1mac(k)][j][i] + f[km1mac(k)][j][ip1mac(i)] + f[k][j][i] + f[k][j][ip1mac(i)]) )

#define v2tov3(f,k,j,i) (0.25*(f[km1mac(k)][j][i] + f[km1mac(k)][jp1mac(j)][i] + f[k][j][i] + f[k][jp1mac(j)][i]))

#define c2z_3d(f,k,j,i) (0.125*(f[k][j][i] + f[k][j][ip1mac(i)] + f[k][jp1mac(j)][i] + f[k][jp1mac(j)][ip1mac(i)] + f[kp1mac(k)][j][i] + f[kp1mac(k)][j][ip1mac(i)] + f[kp1mac(k)][jp1mac(j)][i] + f[kp1mac(k)][jp1mac(j)][ip1mac(i)]))

#define z2c_3d(f,k,j,i) (0.125*(f[k][jm1mac(j)][im1mac(i)] + f[k][jm1mac(j)][i] + f[k][j][im1mac(i)] + f[k][j][i] + f[kp1mac(k)][jm1mac(j)][im1mac(i)] + f[kp1mac(k)][jm1mac(j)][i] + f[kp1mac(k)][j][im1mac(i)] + f[kp1mac(k)][j][i]) )

#define z2c_2(f,k,j,i) (0.25*(f[km1mac(k)][j][im1mac(i)] + f[km1mac(k)][j][i] + f[k][j][im1mac(i)] + f[k][j][i]))

#define c2z_2(f,k,j,i) (0.25*(f[k][j][i] + f[k][j][ip1mac(i)] + f[kp1mac(k)][j][i] + f[kp1mac(k)][j][ip1mac(i)]))

#define z2c_1(f,k,j,i) (0.25*(f[km1mac(k)][jm1mac(j)][i] + f[km1mac(k)][j][i] + f[k][jm1mac(j)][i] + f[k][j][i]) )

#define c2z_1(f,k,j,i) (0.25*(f[k][j][i] + f[k][jp1mac(j)][i] + f[kp1mac(k)][j][i] + f[kp1mac(k)][jp1mac(j)][i]) )


#elif(LINEARINTERP==0) // not really right at all

#define z2e_1(f,k,j,i) (f[k][j][i])
#define z2e_2(f,k,j,i) (f[k][j][i])
#define z2e_3(f,k,j,i) (f[k][j][i])
#define e2z_1(f,k,j,i) (f[k][j][i])
#define e2z_2(f,k,j,i) (f[k][j][i])
#define e2z_3(f,k,j,i) (f[k][j][i])
#define v2tov1(f,k,j,i) (f[k][j][i])
#define v1tov2(f,k,j,i) (f[k][j][i])
#define z2c_3(f,k,j,i) (f[k][j][i])
#define c2z_3(f,k,j,i) (f[k][j][i])

#define v2to050(f,k,j,i) (f[k][j][i])

#define v3to005(f,k,j,i) (f[k][j][i])

#define v3tov1(f,k,j,i)  (f[k][j][i])

#define v3tov2(f,k,j,i)  (f[k][j][i])

#define v1tov3(f,k,j,i)  (f[k][j][i])

#define v2tov3(f,k,j,i)  (f[k][j][i])

#define c2z_3d(f,k,j,i) (f[k][j][i])

#define z2c_3d(f,k,j,i) (f[k][j][i])

#define z2c_2(f,k,j,i) (f[k][j][i])
#define c2z_2(f,k,j,i) (f[k][j][i])


#define z2c_1(f,k,j,i) (f[k][j][i])

#define c2z_1(f,k,j,i)  (f[k][j][i])



#endif

#elif(TVDLF==1) // not really valid right now, but not used


#define z2e_1(f,k,j,i) (f[k][j][i])
#define z2e_2(f,k,j,i) (f[k][j][i])
#define z2e_3(f,k,j,i) (f[k][j][i])
#define e2z_1(f,k,j,i) (f[k][j][i])
#define e2z_2(f,k,j,i) (f[k][j][i])
#define e2z_3(f,k,j,i) (f[k][j][i])
#define v2tov1(f,k,j,i) (f[k][j][i])
#define v1tov2(f,k,j,i) (f[k][j][i])
#define z2c_3(f,k,j,i) (f[k][j][i]) // not really right
#define c2z_3(f,k,j,i) (f[k][j][i]) // not really right

#define v2to050(f,k,j,i) (f[k][j][i]) // not really right

#define v3to005(f,k,j,i) (f[k][j][i]) // not really right

#define v3tov1(f,k,j,i)  (f[k][j][i])

#define v3tov2(f,k,j,i)  (f[k][j][i])

#define v1tov3(f,k,j,i)  (f[k][j][i])

#define v1to500(f,k,j,i) (f[k][j][i]) // not really right

#define v2tov3(f,k,j,i)  (f[k][j][i])

#define c2z_3d(f,k,j,i)  (f[k][j][i])// not really right

#define z2c_3d(f,k,j,i) (f[k][j][i])

#define z2c_2(f,k,j,i) (f[k][j][i])
#define c2z_2(f,k,j,i) (f[k][j][i])

#define z2c_1(f,k,j,i) (f[k][j][i])

#define c2z_1(f,k,j,i)  (f[k][j][i])

#endif




#if((COORD==3)||(COORD==2))

#if(VOLUMEDIFF)

#define deldotv(name,wvec,k,j,i) \
( (G2(1,ip1mac(i))*G3(1,ip1mac(i))*name[wvec][1][k][j][ip1mac(i)]-G2(1,i)*G3(1,i)*name[wvec][1][k][j][i])*ODVL(1,1,i)+\
(G4(1,jp1mac(j))*name[wvec][2][k][jp1mac(j)][i]-G4(1,j)*name[wvec][2][k][j][i])*ODVL(1,2,j)/(G2(2,i)) +\
(name[wvec][3][kp1mac(k)][j][i]-name[wvec][3][k][j][i])*(OARC13(k,j,i)*ODX(1,3,k)) )

#else
// volume terms don't preserve divb=0, so use this for that:
#define deldotv(name,wvec,k,j,i) \
( (G2(1,ip1mac(i))*G3(1,ip1mac(i))*name[wvec][1][k][j][ip1mac(i)]-G2(1,i)*G3(1,i)*name[wvec][1][k][j][i])*ODX(1,1,i)/(G2(2,i)*G3(2,i))+\
(G4(1,jp1mac(j))*name[wvec][2][k][jp1mac(j)][i]-G4(1,j)*name[wvec][2][k][j][i])*ODX(1,2,j)/(G2(2,i)*G4(2,j)) +\
(name[wvec][3][kp1mac(k)][j][i]-name[wvec][3][k][j][i])*(OARC13(k,j,i)*ODX(1,3,k)) )

#endif

#define deldotv2(name,wvec,k,j,i) deldotv(name,wvec,k,j,i)

// gradof v currently only used for tensor viscosity, which isn't working/used right now
// below grads not right for 3d
#define gradv11(name,wvec,k,j,i) \
( (name[wvec][1][k][j][ip1mac(i)]-name[wvec][1][k][j][i])/dx[1][1][i] )

#define gradv22(name,wvec,k,j,i) \
( (name[wvec][2][k][jp1mac(j)][i]-name[wvec][2][k][j][i])/(G2(2,i)*dx[1][2][j])+\
0.5*(name[wvec][1][k][j][i]+name[wvec][1][k][j][ip1mac(i)])/(G2(2,i))*DG2(2,i) )

#define gradv33(name,wvec,k,j,i) \
(0.5*( (name[wvec][1][k][j][i]+name[wvec][1][k][j][ip1mac(i)])/(G3(2,i))*DG3(2,i)+\
(name[wvec][2][k][j][i]+name[wvec][2][k][jp1mac(j)][i])/(G2(2,i)*G4(2,j))*DG4(2,j) ) )

// below assumes normal vector positions for input and output
// assumes vector exists in local and 3 lower-corner&left&right zones in general
// vector is forced to be located at (.5,0,0) curlv2: (0,.5,0) curlv3: (0,0,.5) so the curl will be at vector location

#if(VOLUMEDIFF==0)

#define curlv11(name,k,j,i) (1.0/(G4(2,j)*G2(1,i))*( G4(1,jp1mac(j))*v3to005(name[3],k,jp1mac(j),i)-G4(1,j)*v3to005(name[3],k,j,i) )*ODX(1,2,j))

#define curlv12(name,k,j,i) (-1.0/(G4(2,j)*G3(1,i))*(v2to050(name[2],kp1mac(k),j,i)-v2to050(name[2],k,j,i))*ODX(1,3,k))

// 0 condition here true for non-reflective axis too(i.e. general axis)
#define curlv21(name,k,j,i) ((G4(1,j)==0.0) ?  0.0 : 1.0/(G3(2,i)*G4(1,j))*(v1to500(name[1],kp1mac(k),j,i)-v1to500(name[1],k,j,i))*ODX(1,3,k))

#define curlv22(name,k,j,i) (-1.0/(G3(2,i))*(G3(1,ip1mac(i))*v3to005(name[3],k,j,ip1mac(i))-G3(1,i)*v3to005(name[3],k,j,i) )*ODX(1,1,i))

#define curlv31(name,k,j,i) (1.0/(G2(2,i))*(G2(1,ip1mac(i))*v2to050(name[2],k,j,ip1mac(i))-G2(1,i)*v2to050(name[2],k,j,i))*ODX(1,1,i))

#define curlv32(name,k,j,i) (-1.0/(G2(2,i))*(v1to500(name[1],k,jp1mac(j),i)-v1to500(name[1],k,j,i))*ODX(1,2,j))

// curl forced to result in centered quantity

#define curlcv11(name,k,j,i) (1.0/(G4(2,j)*G2(2,i))*( G4(1,jp1mac(j))*v3tov2(name[3],k,jp1mac(j),i)-G4(1,j)*v3tov2(name[3],k,j,i) )*ODX(1,2,j))

#define curlcv12(name,k,j,i) (-1.0/(G4(2,j)*G3(2,i))*(v2tov3(name[2],kp1mac(k),j,i)-v2tov3(name[2],k,j,i))*ODX(1,3,k))

#define curlcv21(name,k,j,i) (1.0/(G3(2,i)*G4(2,j))*(v1tov3(name[1],kp1mac(k),j,i)-v1tov3(name[1],k,j,i))*ODX(1,3,k))

#define curlcv22(name,k,j,i) (-1.0/(G3(2,i))*(G3(1,ip1mac(i))*v3tov1(name[3],k,j,ip1mac(i))-G3(1,i)*v3tov1(name[3],k,j,i) )*ODX(1,1,i))

#define curlcv31(name,k,j,i) (1.0/(G2(2,i))*(G2(1,ip1mac(i))*v2tov1(name[2],k,j,ip1mac(i))-G2(1,i)*v2tov1(name[2],k,j,i))*ODX(1,1,i))

#define curlcv32(name,k,j,i) (-1.0/(G2(2,i))*(v1tov2(name[1],k,jp1mac(j),i)-v1tov2(name[1],k,j,i))*ODX(1,2,j))


// natural curls, such that a first curl of vector will have curl(v) in curlv1: (.5,0,0) curlv2: (0,.5,0) curlv3: (0,0,.5)
// this is such that a curl of a curl gives back natural vector positions.

// problem if reflect?x?=1 for that ? boundary where term should go to 0 but gets 0/0, so skip that term and just set to 0

// second term 0 also in general axis since same value really and just 0 anyways if reflect, 1st term always 0 by derivative-across-sing condition for all BC
// not sure when general condition about 1st term, but could use volume difference to fix problem ( then should use VOLUMEDIFF version)
#define curlvfornat11(name,k,j,i) ( (G4(1,j)==0.0) ? 0.0 : (1.0/(G4(1,j)*G2(2,i))  *( G4(2,j)*name[3][k][j][i]-G4(2,jm1mac(j))*name[3][k][jm1mac(j)][i] )*ODX(2,2,j)))

#define curlvfornat12(name,k,j,i) ( (G4(1,j)==0.0) ? 0.0 : (-1.0/(G4(1,j)*G3(2,i))*(name[2][k][j][i]-name[2][km1mac(k)][j][i])*ODX(2,3,k)) )

#define curlvfornat21(name,k,j,i) (1.0/(G3(1,i)*G4(2,j)) *(name[1][k][j][i]-name[1][km1mac(k)][j][i])*ODX(2,3,k))

#define curlvfornat22(name,k,j,i) (-1.0/(G3(1,i)) *(G3(2,i)*name[3][k][j][i]-G3(2,im1mac(i))*name[3][k][j][im1mac(i)] )*ODX(2,1,i))

#define curlvfornat31(name,k,j,i) (1.0/(G2(1,i)) * (G2(2,i)*name[2][k][j][i]-G2(2,im1mac(i))*name[2][k][j][im1mac(i)])*ODX(2,1,i))

#define curlvfornat32(name,k,j,i) (-1.0/(G2(1,i)) * (name[1][k][j][i]-name[1][k][jm1mac(j)][i])*ODX(2,2,j))

// the curl to be used on a previously curled thing(like emf), ends up at normal vector positions
//  curlv1: (0,.5,.5) curlv2: (.5,0,.5) curlv3: (.5,.5,0)
#define curlvbacknat11(name,k,j,i) (1.0/(G4(2,j)*G2(1,i))  *(G4(1,jp1mac(j))*name[3][k][jp1mac(j)][i]-G4(1,j)*name[3][k][j][i] )*ODX(1,2,j))

#define curlvbacknat12(name,k,j,i) (-1.0/(G4(2,j)*G3(1,i))  *(name[2][kp1mac(k)][j][i]-name[2][k][j][i])*ODX(1,3,k))

// first term of sum is 0 since same point, 2nd term ok in general
#define curlvbacknat21(name,k,j,i) ( (G4(1,j)==0.0) ? 0.0  : (1.0/(G3(2,i)*G4(1,j)) *(name[1][kp1mac(k)][j][i]-name[1][k][j][i])*ODX(1,3,k)))

#define curlvbacknat22(name,k,j,i) (-1.0/(G3(2,i)) *(G3(1,ip1mac(i))*name[3][k][j][ip1mac(i)]-G3(1,i)*name[3][k][j][i] )*ODX(1,1,i))

#define curlvbacknat31(name,k,j,i) (1.0/(G2(2,i)) * (G2(1,ip1mac(i))*name[2][k][j][ip1mac(i)]-G2(1,i)*name[2][k][j][i])*ODX(1,1,i))

#define curlvbacknat32(name,k,j,i) (-1.0/(G2(2,i)) * (name[1][k][jp1mac(j)][i]-name[1][k][j][i])*ODX(1,2,j))


#else // if volumediff==1


#define curlv11(name,k,j,i) (1.0/G2(1,i)*(G4(1,jp1mac(j))*v3to005(name[3],k,jp1mac(j),i) - G4(1,j)*v3to005(name[3],k,j,i))/DVL(1,2,j))
#define curlv12(name,k,j,i) (-1.0/(G4(2,j)*G3(1,i))*(v2to050(name[2],kp1mac(k),j,i) - v2to050(name[2],k,j,i))*ODX(1,3,k))

// general condition for any boundary type since at same position really
#define curlv21(name,k,j,i) ( (G4(1,j)==0.0) ? 0.0 : 1.0/(G4(1,j)*G3(2,i))*(v1to500(name[1],kp1mac(k),j,i) - v1to500(name[1],k,j,i))*ODX(1,3,k))
#define curlv22(name,k,j,i) (-G2(2,i)*(G3(1,ip1mac(i))*v3to005(name[3],k,j,ip1mac(i)) - G3(1,i)*v3to005(name[3],k,j,i))/DVL(1,1,i))

#define curlv31(name,k,j,i) (G3(2,i)*(G2(1,ip1mac(i))*v2to050(name[2],k,j,ip1mac(i)) - G2(1,i)*v2to050(name[2],k,j,i))/DVL(1,1,i))
#define curlv32(name,k,j,i) (-G4(2,j)/G2(2,i)*(v1to500(name[1],k,jp1mac(j),i) - v1to500(name[1],k,j,i))/DVL(1,2,j))

// curl resulting in centered quantity

#define curlcv11(name,k,j,i) (1.0/G2(2,i)*(G4(1,jp1mac(j))*v3tov2(name[3],k,jp1mac(j),i) - G4(1,j)*v3tov2(name[3],k,j,i))/DVL(1,2,j))
#define curlcv12(name,k,j,i) (-1.0/(G4(2,j)*G3(2,i))*(v2tov3(name[2],kp1mac(k),j,i) - v2tov3(name[2],k,j,i))*ODX(1,3,k))

#define curlcv21(name,k,j,i) (1.0/(G4(2,j)*G3(2,i))*(v1tov3(name[1],kp1mac(k),j,i) - v1tov3(name[1],k,j,i))*ODX(1,3,k))
#define curlcv22(name,k,j,i) (-G2(2,i)*(G3(1,ip1mac(i))*v3tov1(name[3],k,j,ip1mac(i)) - G3(1,i)*v3tov1(name[3],k,j,i))/DVL(1,1,i))

#define curlcv31(name,k,j,i) (G3(2,i)*(G2(1,ip1mac(i))*v2tov1(name[2],k,j,ip1mac(i)) - G2(1,i)*v2tov1(name[2],k,j,i))/DVL(1,1,i))
#define curlcv32(name,k,j,i) (-G4(2,j)/G2(2,i)*(v1tov2(name[1],k,jp1mac(j),i) - v1tov2(name[1],k,j,i))/DVL(1,2,j))

// natural curls, such that a first curl of vector will have curl(v) in curlv1: (.5,0,0) curlv2: (0,.5,0) curlv3: (0,0,.5)
// this is such that a curl of a curl gives back natural vector positions.

// problem if reflect?x?=1 for that ? boundary where term should go to 0 but gets 0/0, so skip that term and just set to 0

// second term 0 also in general axis since same value really and just 0 anyways if reflect
// use volume diff to fix curlvfornat11
#define curlvfornat11(name,k,j,i) (  1.0/(G2(2,i))*( G4(2,j)*name[3][k][j][i]-G4(2,jm1mac(j))*name[3][k][jm1mac(j)][i] )/DVL(2,2,j))
#define curlvfornat12(name,k,j,i) ( (G4(1,j)==0.0) ? 0.0 : -1.0/(G4(1,j)*G3(2,i))*(name[2][k][j][i]-name[2][km1mac(k)][j][i])*ODX(2,3,k))

#define curlvfornat21(name,k,j,i) ( 1.0/(G3(1,i)*G4(2,j))*(name[1][k][j][i]-name[1][km1mac(k)][j][i])*ODX(2,3,k))
#define curlvfornat22(name,k,j,i) (-G2(1,i)*( G3(2,i)*name[3][k][j][i]-G3(2,im1mac(i))*name[3][k][j][im1mac(i)] )/DVL(2,1,i))

#define curlvfornat31(name,k,j,i) (G3(1,i)*(G2(2,i)*name[2][k][j][i]-G2(2,im1mac(i))*name[2][k][j][im1mac(i)])/DVL(2,1,i))
#define curlvfornat32(name,k,j,i) (-G4(1,j)/G2(1,i)*(name[1][k][j][i]-name[1][k][jm1mac(j)][i])/DVL(2,2,j))

// the curl to be used on a previously curled thing(like emf), ends up at normal vector positions
//  curlv1: (0,.5,.5) curlv2: (.5,0,.5) curlv3: (.5,.5,0)

#define curlvbacknat11(name,k,j,i) (1.0/G2(1,i)*(G4(1,jp1mac(j))*name[3][k][jp1mac(j)][i] - G4(1,j)*name[3][k][j][i])/DVL(1,2,j))
#define curlvbacknat12(name,k,j,i) (-1.0/(G4(2,j)*G3(1,i))*(name[2][kp1mac(k)][j][i] - name[2][k][j][i])*ODX(1,3,k))

// general condition for any boundary type since at same position really
#define curlvbacknat21(name,k,j,i) ( (G4(1,j)==0.0) ? 0.0 : 1.0/(G4(1,j)*G3(2,i))*(name[1][kp1mac(k)][j][i] - name[1][k][j][i])*ODX(1,3,k))
#define curlvbacknat22(name,k,j,i) (-G2(2,i)*(G3(1,ip1mac(i))*name[3][k][j][ip1mac(i)] - G3(1,i)*name[3][k][j][i])/DVL(1,1,i))

#define curlvbacknat31(name,k,j,i) (G3(2,i)*(G2(1,ip1mac(i))*name[2][k][j][ip1mac(i)] - G2(1,i)*name[2][k][j][i])/DVL(1,1,i))
#define curlvbacknat32(name,k,j,i) (-G4(2,j)/G2(2,i)*(name[1][k][jp1mac(j)][i] - name[1][k][j][i])/DVL(1,2,j))

#endif // endif volumediff==0 or 1


#elif(COORD==1) // volume diff and normal diff same

#define deldotv(name,wvec,k,j,i) \
( (name[wvec][1][k][j][ip1mac(i)]-name[wvec][1][k][j][i])*ODX(1,1,i)+\
(name[wvec][2][k][jp1mac(j)][i]-name[wvec][2][k][j][i])*ODX(1,2,j) +\
(name[wvec][3][kp1mac(k)][j][i]-name[wvec][3][k][j][i])*ODX(1,3,k) )

// volume terms don't preserve divb=0, so use this for that:
#define deldotv2(name,wvec,k,j,i) deldotv(name,wvec,k,j,i)

// gradof v currently only used for tensor viscosity, which isn't working/used right now
#define gradv11(name,wvec,k,j,i) \
( (name[wvec][1][k][j][ip1mac(i)]-name[wvec][1][k][j][i])*ODX(1,1,i) )

#define gradv22(name,wvec,k,j,i) \
( (name[wvec][2][k][jp1mac(j)][i]-name[wvec][2][k][j][i])*ODX(1,2,j) )

#define gradv33(name,wvec,k,j,i) \
( (name[wvec][3][kp1mac(k)][j][i]-name[wvec][3][k][j][i])*ODX(1,3,k) )

// below assumes normal vector positions for input and output
// assumes vector exists in local and 3 lower-corner&left&right zones in general
// vector is forced to be located at (.5,0,0) curlv2: (0,.5,0) curlv3: (0,0,.5) so the curl will be at vector location
#define curlv11(name,k,j,i) (( v3to005(name[3],k,jp1mac(j),i)-v3to005(name[3],k,j,i) )*ODX(1,2,j))

#define curlv12(name,k,j,i) (-(v2to050(name[2],kp1mac(k),j,i)-v2to050(name[2],k,j,i))*ODX(1,3,k))

#define curlv21(name,k,j,i) ((v1to500(name[1],kp1mac(k),j,i)-v1to500(name[1],k,j,i))*ODX(1,3,k))

#define curlv22(name,k,j,i) (-(v3to005(name[3],k,j,ip1mac(i))-v3to005(name[3],k,j,i) )*ODX(1,1,i))

#define curlv31(name,k,j,i) ( (v2to050(name[2],k,j,ip1mac(i))-v2to050(name[2],k,j,i))*ODX(1,1,i))

#define curlv32(name,k,j,i) ( - (v1to500(name[1],k,jp1mac(j),i)-v1to500(name[1],k,j,i))*ODX(1,2,j))

// curl resulting in centered quantity

#define curlcv11(name,k,j,i) ((v3tov2(name[3],k,jp1mac(j),i) - v3tov2(name[3],k,j,i))*ODX(1,2,j))
#define curlcv12(name,k,j,i) ((v2tov3(name[2],kp1mac(k),j,i) - v2tov3(name[2],k,j,i))*ODX(1,3,k))

#define curlcv21(name,k,j,i) ((v1tov3(name[1],kp1mac(k),j,i) - v1tov3(name[1],k,j,i))*ODX(1,3,k))
#define curlcv22(name,k,j,i) ((v3tov1(name[3],k,j,ip1mac(i)) - v3tov1(name[3],k,j,i))*ODX(1,1,i))

#define curlcv31(name,k,j,i) ((v2tov1(name[2],k,j,ip1mac(i)) - v2tov1(name[2],k,j,i))*ODX(1,1,i))
#define curlcv32(name,k,j,i) ((v1tov2(name[1],k,jp1mac(j),i) - v1tov2(name[1],k,j,i))*ODX(1,2,j))


// natural curls, such that a first curl of vector will have curl(v) in curlv1: (.5,0,0) curlv2: (0,.5,0) curlv3: (0,0,.5)
// this is such that a curl of a curl gives back natural vector positions.

// problem if reflect?x?=1 for that ? boundary where term should go to 0 but gets 0/0, so skip that term and just set to 0

#define curlvfornat11(name,k,j,i) (  ( name[3][k][j][i]-name[3][k][jm1mac(j)][i] )*ODX(2,2,j) )

#define curlvfornat12(name,k,j,i) ( - (name[2][k][j][i]-name[2][km1mac(k)][j][i])*ODX(2,3,k))

#define curlvfornat21(name,k,j,i) ((name[1][k][j][i]-name[1][km1mac(k)][j][i])*ODX(2,3,k) )

#define curlvfornat22(name,k,j,i) ( - ( name[3][k][j][i]-name[3][k][j][im1mac(i)] )*ODX(2,1,i) )

#define curlvfornat31(name,k,j,i) ( (name[2][k][j][i]-name[2][k][j][im1mac(i)])*ODX(2,1,i) )

#define curlvfornat32(name,k,j,i) ( - (name[1][k][j][i]-name[1][k][jm1mac(j)][i])*ODX(2,2,j) )


#define curlvbacknat11(name,k,j,i) ((name[3][k][jp1mac(j)][i]-name[3][k][j][i] )*ODX(1,2,j))

#define curlvbacknat12(name,k,j,i) ( - (name[2][kp1mac(k)][j][i]-name[2][k][j][i])*ODX(1,3,k))

#define curlvbacknat21(name,k,j,i) ( (name[1][kp1mac(k)][j][i]-name[1][k][j][i])*ODX(1,3,k) )

#define curlvbacknat22(name,k,j,i) ( - ( name[3][k][j][ip1mac(i)]-name[3][k][j][i] )*ODX(1,1,i) )

#define curlvbacknat31(name,k,j,i) ( (name[2][k][j][ip1mac(i)]-name[2][k][j][i])*ODX(1,1,i) )

#define curlvbacknat32(name,k,j,i) ( - (name[1][k][jp1mac(j)][i]-name[1][k][j][i])*ODX(1,2,j) )

#endif // endif coord==1


    // nifty macros
#define curlv1(name,k,j,i) (curlv11(name,k,j,i)+curlv12(name,k,j,i))
#define curlv2(name,k,j,i) (curlv21(name,k,j,i)+curlv22(name,k,j,i))
#define curlv3(name,k,j,i) (curlv31(name,k,j,i)+curlv32(name,k,j,i))

#define curlvfornat1(name,k,j,i) (curlvfornat11(name,k,j,i)+curlvfornat12(name,k,j,i))
#define curlvfornat2(name,k,j,i) (curlvfornat21(name,k,j,i)+curlvfornat22(name,k,j,i))
#define curlvfornat3(name,k,j,i) (curlvfornat31(name,k,j,i)+curlvfornat32(name,k,j,i))

#define curlvbacknat1(name,k,j,i) (curlvbacknat11(name,k,j,i)+curlvbacknat12(name,k,j,i))
#define curlvbacknat2(name,k,j,i) (curlvbacknat21(name,k,j,i)+curlvbacknat22(name,k,j,i))
#define curlvbacknat3(name,k,j,i) (curlvbacknat31(name,k,j,i)+curlvbacknat32(name,k,j,i))


#if(COORD>1)


// b?p: to be used on outer edge
// b?m: to be u sed on inner edge
#if(VOLUMEDIFF==0)

#if(N1>1)
#define b1p(name,k,j,i) ( dx[1][1][im1mac(i)]*(G2(1,im1mac(i))*G3(1,im1mac(i))*G4(2,j)*ODX(1,1,im1mac(i))*name[1][k][j][im1mac(i)] + G3(2,im1mac(i))*ODX(1,2,j)*(G4(1,j)*name[2][k][j][im1mac(i)] - G4(1,jp1mac(j))*name[2][k][jp1mac(j)][im1mac(i)]) + G2(2,im1mac(i))*ODX(1,3,k)*(name[3][k][j][im1mac(i)] - name[3][kp1mac(k)][j][im1mac(i)]))/(G2(1,i)*G3(1,i)*G4(2,j)) )

#define b1m(name,k,j,i) ( dx[1][1][i]*(G2(1,ip1mac(i))*G3(1,ip1mac(i))*G4(2,j)*ODX(1,1,i)*name[1][k][j][ip1mac(i)] + G3(2,i)*ODX(1,2,j)*(-G4(1,j)*name[2][k][j][i] + G4(1,jp1mac(j))*name[2][k][jp1mac(j)][i]) + G2(2,i)*ODX(1,3,k)*(-name[3][k][j][i] + name[3][kp1mac(k)][j][i]))/(G2(1,i)*G3(1,i)*G4(2,j)))

#else
#define b1p(name,k,j,i) (name[1][k][j][i])
#define b1m(name,k,j,i) (name[1][k][j][i])
#endif

#if(N2>1)

// for b2p/m: b2 can be anything along polar axis and will conserve divB=0, so just set to original value (i.e. don't change)
#define b2p(name,k,j,i) ( (G4(1,j)==0.0) ? name[2][k][j][i] : ( dx[1][2][jm1mac(j)]*(G4(2,jm1mac(j))*ODX(1,1,i)*(G2(1,i)*G3(1,i)*name[1][k][jm1mac(j)][i] - G2(1,ip1mac(i))*G3(1,ip1mac(i))*name[1][k][jm1mac(j)][ip1mac(i)]) + G4(1,jm1mac(j))*G3(2,i)*ODX(1,2,jm1mac(j))*name[2][k][jm1mac(j)][i] + G2(2,i)*ODX(1,3,k)*(name[3][k][jm1mac(j)][i] - name[3][kp1mac(k)][jm1mac(j)][i]))/(G4(1,j)*G3(2,i))) )

#define b2m(name,k,j,i) ( (G4(1,j)==0.0) ? name[2][k][j][i] : ( dx[1][2][j]*(G4(2,j)*ODX(1,1,i)*(-G2(1,i)*G3(1,i)*name[1][k][j][i] + G2(1,ip1mac(i))*G3(1,ip1mac(i))*name[1][k][j][ip1mac(i)]) + G4(1,jp1mac(j))*G3(2,i)*ODX(1,2,j)*name[2][k][jp1mac(j)][i] + G2(2,i)*ODX(1,3,k)*(-name[3][k][j][i] + name[3][kp1mac(k)][j][i]))/(G4(1,j)*G3(2,i))) )


#else
#define b2p(name,k,j,i) (name[2][k][j][i])
#define b2m(name,k,j,i) (name[2][k][j][i])
#endif

#if(N3>1)

#define b3p(name,k,j,i) ( dx[1][3][km1mac(k)]*(G4(2,j)*ODX(1,1,i)*(G2(1,i)*G3(1,i)*name[1][km1mac(k)][j][i] - G2(1,ip1mac(i))*G3(1,ip1mac(i))*name[1][km1mac(k)][j][ip1mac(i)]) + G3(2,i)*ODX(1,2,j)*(G4(1,j)*name[2][km1mac(k)][j][i] - G4(1,jp1mac(j))*name[2][km1mac(k)][jp1mac(j)][i]) + G2(2,i)*ODX(1,3,km1mac(k))*name[3][km1mac(k)][j][i])/(G2(2,i)))

#define b3m(name,k,j,i) ( dx[1][3][k]*(G4(2,j)*ODX(1,1,i)*(-G2(1,i)*G3(1,i)*name[1][k][j][i] + G2(1,ip1mac(i))*G3(1,ip1mac(i))*name[1][k][j][ip1mac(i)]) + G3(2,i)*ODX(1,2,j)*(-G4(1,j)*name[2][k][j][i] + G4(1,jp1mac(j))*name[2][k][jp1mac(j)][i]) + G2(2,i)*ODX(1,3,k)*name[3][kp1mac(k)][j][i])/(G2(2,i)))

#else
#define b3p(name,k,j,i) (name[3][k][j][i])
#define b3m(name,k,j,i) (name[3][k][j][i])
#endif

#else // else if volumediff==1

#if(N1>1)
#define b1p(name,k,j,i) (-1.0/(G2(1,i)*G3(1,i)*ODVL(1,1,im1mac(i)))*(-G2(1,im1mac(i))*G3(1,im1mac(i))*ODVL(1,1,im1mac(i))*name[1][k][j][im1mac(i)] +  1.0/(G2(2,im1mac(i)))*ODVL(1,2,j)*(-G4(1,j)*name[2][k][j][im1mac(i)] + G4(1,jp1mac(j))*name[2][k][jp1mac(j)][im1mac(i)]) + (1.0/(G3(2,im1mac(i))*G4(2,j)))*ODX(1,3,k)*(-name[3][k][j][im1mac(i)] + name[3][kp1mac(k)][j][im1mac(i)])  ) )

#define b1m(name,k,j,i) (1.0/(G2(1,i)*G3(1,i)*ODVL(1,1,i))*(G2(1,ip1mac(i))*G3(1,ip1mac(i))*ODVL(1,1,i)*name[1][k][j][ip1mac(i)] + 1.0/G2(2,i)*(ODVL(1,2,j)*(-G4(1,j)*name[2][k][j][i] + G4(1,jp1mac(j))*name[2][k][jp1mac(j)][i])) + 1.0/(G3(2,i)*G4(2,j))*(ODX(1,3,k)*(-name[3][k][j][i] + name[3][kp1mac(k)][j][i]))))
#else
#define b1p(name,k,j,i) (name[1][k][j][i])
#define b1m(name,k,j,i) (name[1][k][j][i])
#endif

#if(N2>1)
// for b2p/m: b2 can be anything along polar axis and will conserve divB=0, so just set original value (i.e. don't change)
#define b2p(name,k,j,i) ( (G4(1,j)==0.0) ? name[2][k][j][i] : (-G2(2,i)/(G4(1,j)*ODVL(1,2,jm1mac(j)))*(ODVL(1,1,i)*(-G2(1,i)*G3(1,i)*name[1][k][jm1mac(j)][i] + G2(1,ip1mac(i))*G3(1,ip1mac(i))*name[1][k][jm1mac(j)][ip1mac(i)]) - 1.0/G2(2,i)*(G4(1,jm1mac(j))*ODVL(1,2,jm1mac(j))*name[2][k][jm1mac(j)][i]) + 1.0/(G3(2,i)*G4(2,jm1mac(j)))*(ODX(1,3,k)*(-name[3][k][jm1mac(j)][i] + name[3][kp1mac(k)][jm1mac(j)][i])) ) ) )

#define b2m(name,k,j,i) ( (G4(1,j)==0.0) ? name[2][k][j][i] : (G2(2,i)/(G4(1,j)*ODVL(1,2,j))*(ODVL(1,1,i)*(-G2(1,i)*G3(1,i)*name[1][k][j][i] + G2(1,ip1mac(i))*G3(1,ip1mac(i))*name[1][k][j][ip1mac(i)]) + 1.0/(G2(2,i))*(G4(1,jp1mac(j))*ODVL(1,2,j)*name[2][k][jp1mac(j)][i])+ 1.0/(G3(2,i)*G4(2,j))*(ODX(1,3,k)*(-name[3][k][j][i] + name[3][kp1mac(k)][j][i]))) ) )

#else
#define b2p(name,k,j,i) (name[2][k][j][i])
#define b2m(name,k,j,i) (name[2][k][j][i])
#endif

#if(N3>1)

#define b3p(name,k,j,i) (1.0/(G2(2,i)*ODX(1,3,km1mac(k)))*(G3(2,i)*G4(2,j)*(G2(2,i)*ODVL(1,1,i)*(G2(1,i)*G3(1,i)*name[1][km1mac(k)][j][i] - G2(1,ip1mac(i))*G3(1,ip1mac(i))*name[1][km1mac(k)][j][ip1mac(i)]) + ODVL(1,2,j)*(G4(1,j)*name[2][km1mac(k)][j][i] - G4(1,jp1mac(j))*name[2][km1mac(k)][jp1mac(j)][i]))) +name[3][km1mac(k)][j][i])

#define b3m(name,k,j,i) (1.0/(G2(2,i)*ODX(1,3,k))*(G3(2,i)*G4(2,j)*(G2(2,i)*ODVL(1,1,i)*(-G2(1,i)*G3(1,i)*name[1][k][j][i] + G2(1,ip1mac(i))*G3(1,ip1mac(i))*name[1][k][j][ip1mac(i)]) + ODVL(1,2,j)*(-G4(1,j)*name[2][k][j][i] + G4(1,jp1mac(j))*name[2][k][jp1mac(j)][i]))) +name[3][kp1mac(k)][j][i] )

#else
#define b3p(name,k,j,i) (name[3][k][j][i])
#define b3m(name,k,j,i) (name[3][k][j][i])
#endif


#endif // endif volumediff=1

#else // else if COORD==1
// no need for volume way

#if(N1>1)
#define b1p(name,k,j,i) ( dx[1][1][im1mac(i)]*(ODX(1,1,im1mac(i))*name[1][k][j][im1mac(i)] + ODX(1,2,j)*(name[2][k][j][im1mac(i)] - name[2][k][jp1mac(j)][im1mac(i)]) + ODX(1,3,k)*(name[3][k][j][im1mac(i)] - name[3][kp1mac(k)][j][im1mac(i)])) )

#define b1m(name,k,j,i) ( dx[1][1][i]*(ODX(1,1,i)*name[1][k][j][ip1mac(i)] + ODX(1,2,j)*(-name[2][k][j][i] + name[2][k][jp1mac(j)][i]) + ODX(1,3,k)*(-name[3][k][j][i] + name[3][kp1mac(k)][j][i])))

#else
#define b1p(name,k,j,i) (name[1][k][j][i])
#define b1m(name,k,j,i) (name[1][k][j][i])
#endif

#if(N2>1)

#define b2p(name,k,j,i) ( dx[1][2][jm1mac(j)]*(ODX(1,1,i)*(name[1][k][jm1mac(j)][i] - name[1][k][jm1mac(j)][ip1mac(i)]) + ODX(1,2,jm1mac(j))*name[2][k][jm1mac(j)][i] + ODX(1,3,k)*(name[3][k][jm1mac(j)][i] - name[3][kp1mac(k)][jm1mac(j)][i])))

#define b2m(name,k,j,i) ( dx[1][2][j]*(ODX(1,1,i)*(-name[1][k][j][i] + name[1][k][j][ip1mac(i)]) + ODX(1,2,j)*name[2][k][jp1mac(j)][i] + ODX(1,3,k)*(-name[3][k][j][i] + name[3][kp1mac(k)][j][i])))


#else
#define b2p(name,k,j,i) (name[2][k][j][i])
#define b2m(name,k,j,i) (name[2][k][j][i])
#endif

#if(N3>1)

#define b3p(name,k,j,i) ( dx[1][3][km1mac(k)]*(ODX(1,1,i)*(name[1][km1mac(k)][j][i] - name[1][km1mac(k)][j][ip1mac(i)]) + ODX(1,2,j)*(name[2][km1mac(k)][j][i] - name[2][km1mac(k)][jp1mac(j)][i]) + ODX(1,3,km1mac(k))*name[3][km1mac(k)][j][i]))

#define b3m(name,k,j,i) ( dx[1][3][k]*(ODX(1,1,i)*(-name[1][k][j][i] + name[1][k][j][ip1mac(i)]) + ODX(1,2,j)*(-name[2][k][j][i] + name[2][k][jp1mac(j)][i]) + ODX(1,3,k)*name[3][kp1mac(k)][j][i]))

#else
#define b3p(name,k,j,i) (name[3][k][j][i])
#define b3m(name,k,j,i) (name[3][k][j][i])
#endif



#endif// coord==1
