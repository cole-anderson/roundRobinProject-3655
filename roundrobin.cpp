/*
  COLE ANDERSON
  CPSC 3655
  ROUND ROBIN IMPLEMENTATION
*/
#include<iostream>
#include<vector>
#include<stdlib.h>

//Process Struct:
struct processS{
  int id;
  int arrivalT;//sys time where it arrives
  float requiredT;//time required to finish
  float exeT;//time spent executing(increments until == required T)
  int finishT;//sys time when it finishes
  int waitT;
  int completed;
};

//Queues:
std::vector<processS> readyQueue;
std::vector<processS> cpu;
const int q = 1;//q quantum

int main(void)
{
  //test cases:
  // int pNum = 5;
  // processS process[pNum];
  // process[0].arrivalT = 0;
  // process[1].arrivalT = 0;
  // process[2].arrivalT = 4;
  // process[3].arrivalT = 6;//
  // process[4].arrivalT = 8;//
  // process[0].requiredT = 3;
  // process[1].requiredT = 6;
  // process[2].requiredT = 4;
  // process[3].requiredT = 5;
  // process[4].requiredT = 2;//
  // process[0].id = 0;
  // process[1].id = 1;
  // process[2].id = 2;
  // process[3].id = 3;
  // process[4].id = 4;//
  // process[0].exeT = 0;
  // process[1].exeT = 0;
  // process[2].exeT = 0;
  // process[3].exeT = 0;
  // process[4].exeT = 0;//
  // process[0].completed = 0;
  // process[1].completed = 0;
  // process[2].completed = 0;
  // process[3].completed = 0;
  // process[4].completed = 0;//



  //Create array of processes from user input:
  //TODO //UN COMMENT
  int pNum;//process #
  std::cout << "Enter Number of Processes" << std::endl;
  std::cin >>pNum;
  processS process[pNum];


  //Ask for information in relation to each process:
  for(int i = 0; i < pNum; i++)
  {
  std::cout << "Enter Arrival and Required Time" << std::endl;
  std::cin >> process[i].arrivalT >> process[i].requiredT;
  process[i].id = i;
  process[i].exeT = 0;
  process[i].completed = 0;
  std::cout << "Process" << process[i].id << "|Arrival: " << process[i].arrivalT << "|Required: "<< process[i].requiredT << std::endl;
  }
  std::cout <<std::endl;
  std::cout <<std::endl;
  std::cout <<std::endl;

  /*
  loop:
    x(clock time) y(process in execution) z(arriving process) s'(next process in ready queue)
    at Time x: We start process y execution and increment a clock +1
      check for a) arrival z b) process in ready queue
      if arrival && ready queue :: add arrival z to end of ready Q THEN add y to end of ready Q (behind z) -> start execution of s' at start of ready queue
      if arrival && !ready queue :: add y to end of ready queue (y = s') -> start s' at start of ready queue
      if !arrival && ready queue :: add y to end of ready queue (y != s') -> start s' at start of ready queue
      if !arrival && !ready queue :: continue y
      (return top of loop)

      //finish - arrival = turnaround
  */
  //PUT INTO FUNCTION:
  int prev;
  int arr = 0;
  int t = 0;
  int complete = 0;
  int d = 0;

  while(arr != pNum && complete != pNum)//while there are processes in execution
  {

    if(arr != pNum)//if processes are still arriving (1)
    {
    int r = 0;

    for(r = 0; r <= pNum; r++)
    {


      //DEBUG FOR INFINITE LOOP:
      // if(t == 10)
      // {
      //   std::cout << "///TIMEOUT" << std::endl;
      //   std::exit (EXIT_FAILURE);
      // }

      if (process[r].arrivalT == t)//checks if current time a process arrives
      {
        //DEBUG FOR DISPLAYING PROCESSES
        // for(int i = 0; i < pNum; i++)
        // {
        //   std::cout << "Process: " <<process[i].id << " Arrival Time: " << process[i].arrivalT << " Required Time: " << process[i].requiredT << " Execution Time: " << process[i].exeT << std::endl;
        // }
        //

        if(readyQueue.empty() && cpu.empty())//WORKS!! //1
        {
          //std::cout << "//IF1(empty q and empty cpu)" << std::endl;//Debug

          //PLACED PROCESS IN cpu:
          std::cout << "**AT TIME** " << t << std::endl;
          std::cout <<std::endl;
          std::cout << "Process" << process[r].id << " ARRIVES" << std::endl;
          std::cout << "^ENTERS cpu" << std::endl;
          std::cout <<std::endl;
          //Update exeT (execution time)
          cpu.push_back(process[r]);
          process[cpu[0].id].exeT ++;
          prev = cpu[r].id;//temp value

          //extra process
          for(int b = r + 1; b <= pNum; b++)
          {
            if(process[b].arrivalT == t)
            {
              std::cout << "Process" << process[b].id << "ALSO ARRIVES" << std::endl;
              std::cout << "^ENTERS READY QUEUE" << std::endl;
              readyQueue.push_back(process[b]);

            }
          }
          r = pNum;


        }
        else if(readyQueue.empty() && !cpu.empty()) //2
        {

          //std::cout << "//IF2(empty q and !empty cpu)" << std::endl;//debug

          std::cout << "**AT TIME** " << t << std::endl;
          std::cout <<std::endl;
          std::cout << "Process" << process[r].id << " ARRIVES" << std::endl;
          std::cout << "^ENTERS READY QUEUE" << std::endl;
          std::cout <<std::endl;
          readyQueue.push_back(process[r]);
          //extra process
          for(int b = r + 1; b <= pNum; b++)
          {
            if(process[b].arrivalT == t)
            {
              std::cout << "Process" << process[r].id << "ALSO ARRIVES" << std::endl;
              std::cout << "^ENTERS READY QUEUE" << std::endl;
              readyQueue.push_back(process[b]);
            }
          }


          //Check if Process in cpu is done executing if yes update token if no put on ready Q
          if(process[cpu[0].id].exeT == process[cpu[0].id].requiredT && process[cpu[0].id].completed == 0)//a
          {
            std::cout <<"Process" << cpu.front().id << std::endl;
            std::cout << "^EXITS cpu COMPLETE" << std::endl;
            std::cout <<std::endl;
            process[cpu[0].id].completed = 1;
            process[cpu[0].id].finishT = t;
            complete ++;//update # of completed processes

            cpu.clear();//free cpu
          }
          else if(process[cpu[0].id].exeT != process[cpu[0].id].requiredT && process[cpu[0].id].completed == 0)//b
          {//if
            std::cout <<"Process" << cpu.front().id << std::endl;
            std::cout << "^EXITS cpu ENTERS READY QUEUE" << std::endl;
            std::cout <<std::endl;
            readyQueue.push_back(process[cpu[0].id]);

            cpu.clear();//free cpu
          }

          //NEXT:
          std::cout << "Process" << process[r].id << std::endl;
          std::cout << "^ENTERS cpu(FROM READY Q)" << std::endl;
          std::cout <<std::endl;
          cpu.push_back(process[r]);
          process[cpu[0].id].exeT ++;
          readyQueue.erase(readyQueue.begin());
          prev = cpu[r].id;
          r = pNum;

        }
        else if(!readyQueue.empty() && !cpu.empty()) //3
        {
          //std::cout << "//IF3 (!empty q and !empty cpu)" << std::endl;//debug
          //std::cout << "///VECTOR DEBUG: FRONT OF QUEUE BEFORE ARRIVAL PUSHBACK " << readyQueue.front().id << std::endl;//debug


          std::cout << "**AT TIME** " << t << std::endl;
          std::cout <<std::endl;
          std::cout <<"Process" << process[r].id << " Arrives" << std::endl;
          std::cout << "^ENTERS READY QUEUE" << std::endl;
          std::cout <<std::endl;
          readyQueue.push_back(process[r]);

          for(int b = r + 1; b <= pNum; b++)
          {

            if(process[b].arrivalT == t)
            {

              std::cout << "Process" << process[b].id << "ALSO ARRIVES" << std::endl;
              std::cout << "^ENTERS READY QUEUE" << std::endl;
              readyQueue.push_back(process[b]);


            }
          }


          if(process[cpu[0].id].exeT == process[cpu[0].id].requiredT && process[cpu[0].id].completed == 0)//a
          {
            std::cout <<"Process" << cpu.front().id << std::endl;
            std::cout << "^EXITS cpu COMPLETE" << std::endl;
            std::cout <<std::endl;
            process[cpu[0].id].completed = 1;
            process[cpu[0].id].finishT = t;
            complete ++;//update # of completed processes

            cpu.clear();//free cpu
          }
          else if(process[cpu[0].id].exeT != process[cpu[0].id].requiredT && process[cpu[0].id].completed == 0)//b
          {//if

            std::cout <<"Process" << cpu.front().id << std::endl;
            std::cout << "^EXITS cpu ENTERS READY QUEUE" << std::endl;
            std::cout <<std::endl;
            readyQueue.push_back(process[cpu[0].id]);

            cpu.clear();//free cpu
          }

          //NEXT:
          std::cout << "Process" << readyQueue.front().id << std::endl;
          std::cout << "^ENTERS cpu(FROM READY Q)" << std::endl;
          std::cout <<std::endl;
          cpu.push_back(process[readyQueue.front().id]);
          process[readyQueue.front().id].exeT ++;

          readyQueue.erase(readyQueue.begin());

          prev = cpu[r].id;
          r = pNum;

        }
        arr++;//updates # or arrivals

        std::cout <<std::endl;
        //std::cout << "t1-" << t << std::endl;
        std::cout << "------------------------END TIME SLICE------------------------" << std::endl;//debug
        std::cout <<std::endl;
        t++;

      }//end if
      else if(r == pNum)
      {

        std::cout << "**AT TIME** " << t << std::endl;
        std::cout <<std::endl;

        if(readyQueue.empty() && !cpu.empty())
        {
          if(process[cpu[0].id].exeT == process[cpu[0].id].requiredT && process[cpu[0].id].completed == 0)
          {
            std::cout <<"Process" << cpu.front().id << std::endl;
            std::cout << "^EXITS cpu COMPLETE" << std::endl;
            std::cout <<std::endl;
            process[cpu[0].id].completed = 1;
            process[cpu[0].id].finishT = t;
            complete ++;//update # of completed processes

            cpu.clear();//free cpu
          }
          else if(process[cpu[0].id].exeT != process[cpu[0].id].requiredT && process[cpu[0].id].completed == 0)
          {
            std::cout <<"Process" << cpu.front().id << std::endl;
            std::cout << "^CONTINUES EXECUTION(empty q no new processes)" << std::endl;
            std::cout <<std::endl;
            process[cpu[0].id].exeT ++;// xxx
          }

        }
          else if(!readyQueue.empty() && !cpu.empty())
          {
            if(process[cpu[0].id].exeT == process[cpu[0].id].requiredT && process[cpu[0].id].completed == 0)
            {
              std::cout <<"Process" << cpu.front().id << std::endl;
              std::cout << "^EXITS cpu COMPLETE" << std::endl;
              std::cout <<std::endl;
              process[cpu[0].id].completed = 1;
              process[cpu[0].id].finishT = t;

              complete ++;//update # of completed processes

              cpu.clear();//free cpu
            }
            else if(process[cpu[0].id].exeT != process[cpu[0].id].requiredT && process[cpu[0].id].completed == 0)
            {
              std::cout <<"Process" << cpu.front().id << std::endl;
              std::cout << "^EXITS cpu ENTERS READY QUEUE" << std::endl;
              std::cout <<std::endl;

              readyQueue.push_back(process[cpu[0].id]); // && breakpoint prev or r

              cpu.clear();//free cpu


            }
            // update ______________________________________________________________________________
            //READY Q -> CPU
            std::cout << "Process" << readyQueue.front().id << std::endl;
            std::cout << "^ENTERS cpu(FROM READY Q)" << std::endl;
            std::cout <<std::endl;
            cpu.push_back(process[readyQueue.front().id]);
            process[readyQueue.front().id].exeT ++;
            readyQueue.erase(readyQueue.begin());

          }
          // else if(!readyQueue.empty() && cpu.empty())
          // {
          //   std::cout << "welcome" << std::endl;
          // }
          // else if(readyQueue.empty() && cpu.empty())
          // {
          //   std::cout << "WASTED TIME" << std::endl;
          // }
          // else if(!readyQueue.empty() && cpu.empty())
          // {
          //   std::cout << "test" << std::endl;
          // }


        if(arr != pNum)// HERE
        {
        //END OF TIME SLICE
        std::cout <<std::endl;
        //std::cout << "t2-" << t << std::endl;
        std::cout << "------------------------END TIME SLICE------------------------" << std::endl;//debug
        std::cout <<std::endl;
        t++;
        }

      }
    }//end of process arrival for loop
  }//end of arrival != pNum if
    //AFTER ALL PROCESSES HAVE ARRIVED WE FINISH ALL THEIR EXECUTIONS
    while(arr == pNum && complete != pNum)
    {

      //quick note this does nothing but seg faulted when i commented it out so!
      for(int i = 0; i < pNum; i++)
      {
        // std::cout << "at t" << t << std::endl;
        // std::cout << "Process: " <<process[i].id << " A: " << process[i].arrivalT << " R: " << process[i].requiredT << " E: " << process[i].exeT <<  "c:" << process[i].completed<< std::endl;
      }


        if(readyQueue.empty() && !cpu.empty())
        {
          //std::cout << "q empty| cpu not empty" << std::endl;//debug

          if(process[cpu[0].id].exeT == process[cpu[0].id].requiredT && process[cpu[0].id].completed == 0)
          {
            std::cout <<"Process" << cpu.front().id << std::endl;
            std::cout << "^EXITS cpu COMPLETE" << std::endl;
            std::cout <<std::endl;
            process[cpu[0].id].completed = 1;
            process[cpu[0].id].finishT = t;
            complete ++;//update # of completed processes

            cpu.clear();//free cpu
          }
          else if(process[cpu[0].id].exeT != process[cpu[0].id].requiredT && process[cpu[0].id].completed == 0)
          {
            std::cout <<"Process" << cpu.front().id << std::endl;
            std::cout << "^CONTINUES EXECUTION(empty q no new processes)" << std::endl;
            std::cout <<std::endl;
            process[cpu[0].id].exeT ++;
          }
        }
        else if(!readyQueue.empty() && !cpu.empty())
        {

          if(process[cpu[0].id].exeT == process[cpu[0].id].requiredT && process[cpu[0].id].completed == 0)
          {
            std::cout <<"Process" << cpu.front().id << std::endl;
            std::cout << "^EXITS cpu COMPLETE" << std::endl;
            std::cout <<std::endl;
            process[cpu[0].id].completed = 1;
            process[cpu[0].id].finishT = t;
            complete ++;//update # of completed processes

            cpu.clear();//free cpu
          }
          else if(process[cpu[0].id].exeT != process[cpu[0].id].requiredT && process[cpu[0].id].completed == 0)
          {
            std::cout <<"Process" << cpu.front().id << std::endl;
            std::cout << "^EXITS cpu ENTERS READY QUEUE" << std::endl;
            std::cout <<std::endl;

            readyQueue.push_back(process[cpu[0].id]);

            cpu.clear();//free cpu


          }
          //READY Q -> CPU
          std::cout << "Process" << readyQueue.front().id << std::endl;
          std::cout << "^ENTERS cpu(FROM READY Q)" << std::endl;
          std::cout <<std::endl;
          cpu.push_back(process[readyQueue.front().id]);
          process[readyQueue.front().id].exeT ++;
          readyQueue.erase(readyQueue.begin());
        }
        else if(!readyQueue.empty() && cpu.empty())
        {
          std::cout << "Process" << readyQueue.front().id << std::endl;
          std::cout << "^ENTERS cpu(FROM READY Q)" << std::endl;
          std::cout <<std::endl;
          cpu.push_back(process[readyQueue.front().id]);
          process[readyQueue.front().id].exeT ++;
          readyQueue.erase(readyQueue.begin());
        }

      //END OF TIME SLICE
      std::cout <<std::endl;
      //std::cout << "t3-" << t << std::endl;
      std::cout << "-------------------------END TIME SLICE------------------------" << std::endl;//debug
      std::cout <<std::endl;
      t++;
    }


}//end of while both arrival != pNum && complete != pNum

  //FINAL DEBUGGER LEAVE HERE:
  // for(int i = 0; i < pNum; i++)
  // {
  //   std::cout << "Process: " <<process[i].id << " Arrival Time: " << process[i].arrivalT << " Required Time: " << process[i].requiredT << " Execution Time: " << process[i].exeT << std::endl;
  //
  // }
  //Calculate and output values
  for(int i = 0; i < pNum; i++)
  {
    float turn  = 0;
    float nTurn = 0;
    std::cout << std::endl;
    std::cout << "Process: " <<process[i].id << std::endl;
    //FinishTime:
    std::cout << "^FINISH TIME: " << process[i].finishT << std::endl;
    //Turnaround Time:
    turn = process[i].finishT - process[i].arrivalT;
    std::cout << "^TURNAROUND TIME: " << turn << std::endl;
    //Normalized TurnaroundTime
    nTurn = turn / process[i].exeT;
    std::cout << "^NORMALIZED TURNAROUND TIME: " << nTurn << std::endl;
    //end

  }

  return 0;
}
