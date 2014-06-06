float covariance(int step, float x_vrai[2],float x_bruit[3]){

int i;
float moyenneX=0.0;
for(i=0;i<step;i++){
moyenneX=moyenneX+xr[i];
moyenneY=moyenneY+yr[i];
moyennetheta=moyennetheta+thetar[i];
}
moyenneX=moyenneX/24;
moyenneY=moyenneY/24;
moyennetheta=moyennetheta/24;
float s=0.0;
for(i=0;i<step;i++)
{
sigmaX=sigmaX+(x[i]-moyenneX)*(x[i]-moyenneX);
sigmaY=sigmaY+(y[i]-moyenneY)*(y[i]-moyenneY);
sigmaTheta=sigmaTheta+(x[i]-moyennetheta)*(theta[i]-moyennetheta);
}


covariance[0][0]=sigmaX*sigmaX;
covariance[1][0]=sigmaY*sigmaX;
covariance[2][0]=sigmatheta*sigmaX;
covariance[0][1]=sigmaX*sigmaY;
covariance[1][1]=sigmaY*sigmaY;
covariance[2][1]=sigmaTheta*sigmaY;
covariance[0][2]=sigmatheta*sigmaX;
covariance[1][2]=sigmatheta*sigmaY;
covariance[2][2]=sigmatheta*sigmatheta;
}