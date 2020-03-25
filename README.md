# ind-prog S 20

Testing solution for task 1 (find-number) and task 2 (fizz-buzz)

## Cloning

This repo contains submodules (repos of the students). To clone with submodules:

```sh
$ git clone --recurse-submodules -j8 https://github.com/Dabudabot/ind-prog
```

or just create folder in [students] dir with student name and inside this dir two directories "find-number" and "fizz-buzz" with solution.cpp. Check the [example] student for example.

In case if students made some updates in their code just run:

```sh
$ git submodule foreach git pull origin master
```

to pull the updates in submodules.

## Building

On my local machine I have Visual Studio 2019 installed, so I use msbuild and cl to build the solutions. However you are free to use any compiler and linker just update [build.cmd].

## Running

In order to test all just run [exec_all.cmd] or if you want someone specific run [exec_custom.cmd] with params (check the script to get what I mean)

During build and run scripts will create the following dirs:

* .intermediate - temporary build objects
* build - executable is here (but it is cleared after each run)
* logs - here you can find test results

    [students]: <https://github.com/Dabudabot/ind-prog/tree/master/students>
    [example]: <https://github.com/Dabudabot/ind-prog/tree/master/students/example>
    [exec_all.cmd]: <https://github.com/Dabudabot/ind-prog/blob/master/exec_all.cmd>
    [exec_custom.cmd]: <https://github.com/Dabudabot/ind-prog/blob/master/exec_custom.cmd>
    [build.cmd]: <https://github.com/Dabudabot/ind-prog/blob/master/build.cmd>

Platform: Windows only