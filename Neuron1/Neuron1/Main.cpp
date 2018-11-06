#include <iostream>
//#include <time.h>

int main()
{

  float inputs[]{ 0.0f,0.0f,0.0f,0.0f,0.0f };
  float n = (sizeof(inputs) / sizeof(inputs[0]));
  float weights[]{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};
  float youts[3];

  float Goal;
  float Yout;
  float w1, w2, w3, w4, w5, w6;
  float rNum;
  float stop;
  bool first = true;
  int loops = 0;
  float EpocSumError;

  float alpha = 0.1;
  float theta = (0.8);
  float theta2 = (-0.1);
  float theta3 = (0.3);
  float thetaD;

  double delta = theta3 / 1000;
  do
  {
    std::cout << "Enter Input 1 - ";
    std::cin >> inputs[0];
    std::cout << "\nEnter Input 2 - ";
    std::cin >> inputs[1];
    std::cout << "\nEnter Goal State - ";
    std::cin >> Goal;
    inputs[2] = inputs[0];
    inputs[3] = inputs[1];

    //srand(time(NULL));
    do
    {
      float err, err2, err3, err5, errD;
      EpocSumError = 0.0f;
      //N1 /////////////////////////////////////////////////////////////////////////////
      if (first == true)
      {
        weights[0] = 0.5;
        weights[1] = 0.4;
        w1 = weights[0];
        w2 = weights[1];
        //rNum = rand() % 100;
        //w1 = (rNum / 100);
        //rNum = rand() % 100;
        //w2 = (rNum / 100);
      }
      else
      {
        err2 = youts[0] * (1-youts[0]) * err * weights[4];
        w1 = w1 + alpha * inputs[0] * err2;
        w2 = w2 + alpha * inputs[1] * err2;
        thetaD = alpha * (-1) * err2;
        theta += thetaD;
      }
      weights[0] = w1;
      weights[1] = w2;
      //first = false;
      float Xin = 0.0f;
      for (int i = 0; i < 2; i++)
      {
        Xin += (inputs[i] * weights[i]);
      }
      std::cout << "N1 X Input - " << Xin << "\n";
      /*float value = (theta + delta);
      float valueNeg = (theta - delta);*/

      ///Sign - alpha > 0 ;  
      //if (Xin >= (theta + delta) && Xin >= (theta - delta))
      //{
      //  Yout = 1;
      //}
      //else
      //{
      //  Yout = -1;
      //}
      ///Step - alpha > 0 ;
      //if (Xin >= theta) //&& Xin >= valueNeg)
      //{
      //  Yout = 1;
      //}
      //else
      //{
      //  Yout = 0;
      //}
      ///Sigmoid - No goal state == Just theta activation function
      float power = -(Xin - theta);
      float e = exp(power);
      float divis = 1.0f + e;
      Yout = 1.0f / divis;
      ///Linear
      //Yout = (Xin-theta);
      std::cout << "N1 Y Output - " << Yout << "\n" << "\n";
      youts[0] = Yout;
      ////N2//////////////////////////////////////////////////////////////////////////////////
      if (first == true)
      {
        weights[2] = 0.9;
        weights[3] = 1.0;
        w3 = weights[2];
        w4 = weights[3];
        //rNum = rand() % 100;
        //w3 = (rNum / 100);
        //rNum = rand() % 100;
        //w4 = (rNum / 100);
      }
      else
      {
        err3 = youts[1] * (1-youts[1]) * err * weights[5];
        w3 = w3 + alpha * inputs[2] * err3;
        w4 = w4 + alpha * inputs[3] * err3;
        thetaD = alpha * (-1) * err3;
        theta2 += thetaD;
      }
      weights[2] = w3;
      weights[3] = w4;
      Xin = 0.0f;
      for (int i = 2; i < 4; i++)
      {
        Xin += (inputs[i] * weights[i]);
      }
      std::cout << "N2 X Input - " << Xin << "\n";
      power = -(Xin - theta2);
      e = exp(power);
      divis = 1.0f + e;
      Yout = 1.0f / divis;
      std::cout << "N2 Y Output - " << Yout << "\n" << "\n";
      youts[1] = Yout;
      ////N3/////////////////////////////////////////////////////////////////////////
      inputs[4] = youts[0];
      inputs[5] = youts[1];
      if (first == true)
      {

        weights[4] = (-1.2);
        weights[5] = 1.1;
        w5 = weights[4];
        w6 = weights[5];
        //rNum = rand() % 100;
        //w5 = (rNum / 100);
        //rNum = rand() % 100;
        //w6 = (rNum / 100);
      }
      else
      {
        errD = alpha * youts[0] * err;
        w5 = w5 + errD;
        errD = alpha * youts[1] * err;
        w5 = w5 + errD;
        w6 = w6 + alpha * youts[1] * err;
        thetaD = alpha * (-1) * err;
        theta3 += thetaD;
      }
      weights[4] = w5;
      weights[5] = w6;
      first = false;
      Xin = 0.0f;
      for (int i = 4; i < 6; i++)
      {
        Xin += (inputs[i] * weights[i]);
      }
      std::cout << "N3 X Input - " << Xin << "\n";
      power = -(Xin - theta3);
      e = exp(power);
      divis = 1.0f + e;
      Yout = 1.0f / divis;
      std::cout << "N3 Y Output - " << Yout << "\n" << "\n";
      err5 = Goal - Yout;

      err = Yout * (1 - Yout)*err5;
      EpocSumError += pow(err5, 2);
      loops++;
      if (loops == 10000)
      {
        break;
      }
      //////////////////////////////////////////////////////////////////////////////////
    } while (EpocSumError > 0.001);//(Yout < (Goal-delta) || Yout >= (Goal + delta)); //Step and Sign Functions

    std::cout << "SUCCESS\n";
    std::cout << "EpocSumError - " << EpocSumError << "\n";
    std::cout << "Loops - " << loops << "\n";
    std::cout << "Weights - w1-3 = " << weights[0] << ", w2-3 = " << weights[1] << ", w1-4 = " << weights[2] << ", w2-4 = " << weights[3] << ", w3-5 = " << weights[4] << ", w4-5 = " << weights[5] << "\n\n";
    std::cin >> stop;
    loops = 0;
  } while (stop != 5);
  
  if (stop != NULL)
  {
    return 0;
  }
}

