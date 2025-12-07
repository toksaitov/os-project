COM 341, Operating Systems
==========================
# Project #4 (Bonus Project)

![BSOD](https://raw.githubusercontent.com/rachmiroff/images/refs/heads/main/auca/com-341/fall-2025/os-project/bsod.png)

Thanks to your hard work on the course, you have built the most basic user-space programs: a toy shell, a task information utility, basic file and text manipulation programs, and even tools to handle a simple file system. Impressed by your progress, the infamous instructor [Sergei Rachmiroff](https://raw.githubusercontent.com/rachmiroff/images/refs/heads/main/auca/com-341/fall-2025/os-project/rach.jpg) has decided to create his magnum opus, the **Rach2** operating system. Unfortunately, he is extremely occupied with appointments to visit his family doctor, Professor [Dahl](https://raw.githubusercontent.com/rachmiroff/images/refs/heads/main/auca/com-341/fall-2025/os-project/dahl.png), so he has decided to entrust you with integrating all this work into an operating system. He understands that this is a lot to ask; for that reason, if you fail or do not attempt the work at all, you will not lose any points in the course. To make things easier for you, you are officially allowed to use AI systems in this project.

In this work, by reading, compiling, and running the provided code, we hope you will at least:

* Learn what hoops one has to jump through to get an x86 CPU ready for work.
* Learn how to create bare-metal applications running in kernel mode without the help of any other OS.
* Learn how to set up various hardware controllers, such as interrupt and timer controllers.
* Learn what interrupts are and how timer interrupts may help build a preemptive scheduler, or how keyboard interrupts may allow you to get data from the keyboard without expensive polling.
* Learn what a simple display driver may look like.
* Learn how a memory management unit (MMU) can be configured to enable paging and virtual memory for kernel isolation.
* Learn what cross-compilation is and how to build a disk image with GRUB and your bare-metal code, ready to run on a personal computer or in an emulation/virtualization system.

By attempting to build a real OS, we hope you will:

* Learn how to build complex systems without advanced knowledge by using modern developer tools such as Large Language Models (LLMs).
* Learn how to carefully design prompts and use agentic versions of LLMs to guide a multistep development process.

## Required Tools

On your machine, you will need a GNU/Linux environment with basic Unix command-line utilities, an x86-64 GCC compiler with 32-bit support enabled, GNU Make, QEMU, and Docker (if you want to build an ISO image). You may also want to install FUSE and other Project #3 dependencies to build an initial RAM disk with KRFFS on your host machine. Most of this software is available on our course server, except for Docker.

## Compilation and Usage

Information on how to compile and run the bare-metal environment using the scripts we provide can be found in the `Readme.md` file in the `rach2` directory. Please read and follow the instructions in that file.

## What to Do

First, bring all the code from our course projects into the appropriate directories.

* Put the `ish` code from the first project into the local `ish` directory. We recommend the first version without piping, since it contains the system call handlers, making it easier to port the program to bare-metal.
* Put your lab programs into the `utils` directory. Hopefully, you were following the recommendation not to depend heavily on the standard library. If so, porting the code will be easier, as with `ish` version 1.
* Put all the code from the third project into the `krffs` directory. You do not have to port the file system utility programs, such as the defragmentation program that you wrote, but the file system code must be ported. We recommend generating code to handle a virtual RAM disk rather than a real disk. GRUB and QEMU can load a file that you create with the host version of KRFFS into memory and provide you with the address and size of that blob in the `k_main` function, as per the Multiboot1 standard. You can manage that area of memory as if it was our mapped file system from the third project. The FUSE system call handling code must be ported as well, of course.
* Put the `tasks` code from the second project into the local `tasks` directory. You may port this program last or choose not to port it at all, as it depends on many high-level libraries that will be challenging to port or replace.

Second, pick a good LLM. You should definitely choose an agentic version, such as Codex CLI, Claude Code, or Gemini CLI. There are free alternatives as well. Some companies serving commercial closed-source LLMs provide free credits for a limited period during the Christmas release season. Take advantage of those opportunities if paying for an LLM is not an option.

Third, clean the code and adapt it to our environment with the help of the chosen LLM. Our bare-metal OS is written to target an older 32-bit x86 mode of execution (still well-supported even by modern 64-bit x86 Intel and AMD chips). This means system calls must be made differently in `ish`. It would be helpful to write inline assembly code for the `utils` programs as well, targeting 32-bit x86 Linux. Essentially, ensure that all programs can compile and run with the `-m32 -mno-sse -mno-sse2` flags under the Ubuntu 24.04 `gcc-multilib` version of the compiler. We also suggest removing comments and eliminating Sergei's peculiar style of maintaining the 80-column limit, as it increases the token count and prevents LLMs from keeping as many files in the context window as possible.

Finally, build a great prompt. Verify it with an LLM and adjust as needed. We recommend instructing the LLM to build an execution plan, carefully documented in a file, and to produce something testable after every major step that you can verify. If something fails after a step, work with the LLM to fix the problem. Once successful, ensure the LLM updates the plan file. Be sure to put each successful step of your code under version control so you can roll back unsuccessful attempts made by the LLM. Proceed step by step, carefully. [Ultrathink](https://www.anthropic.com/engineering/claude-code-best-practices), make no mistakes, and may the phrase _"You are absolutely right!"_ not be something you encounter often in your journey.

### How to Submit

Considering that it is difficult to write a grader for an open project and that it is possible for one student to do the hard work while others submit it as their own to receive free bonus points, we will grade the project in person only. You will need to come on the 22nd of December, the last exam day, during your normal class time and present your work to the instructor. You must be prepared to show your LLM prompts; for that reason, keep them and do not delete them. You will also need to show your commit history. After that, the instructor may ask questions about the process and about your general knowledge from the course. If the prompt history, commit history, and answers about general high-level knowledge are satisfactory, and most components work—meaning the shell and at least several system utilities are all loaded and interacting with the file system on the RAM disk—we may award up to five bonus points. This amount is modest so as not to discourage students from prioritizing regular coursework. We recommend focusing on Project #3 and preparation for the Final Exam in the last two weeks. If after that you have time, definitely try to finish this work. Who knows how powerful modern LLMs have become and how much time you will actually need to spend.

### Deadline

On the 22nd of December, during the usual lecture class time, you may defend your bonus project. If you do not plan to complete the bonus project, you may skip the class. If you are interested in seeing other students' operating systems, do come, even if you are not planning to defend.

## Additional Information

### Web Resources

* [OpenAI Prompt Engineering Guide](https://platform.openai.com/docs/guides/prompt-engineering)
* [Anthropic Prompt Engineering Overview](https://docs.anthropic.com/en/docs/build-with-claude/prompt-engineering/overview)
* [Google Gemini Prompting Strategies](https://ai.google.dev/gemini-api/docs/prompting-strategies)
* [OSDev Wiki](https://wiki.osdev.org/Expanded_Main_Page)

### Books

* _C Programming: A Modern Approach, 2nd Edition by K. N. King_

* _C Programming Language, 2nd Edition by Brian W. Kernighan, Dennis M. Ritchie_

* _Operating System Concepts, 10th Edition by Avi Silberschatz_

* _Operating Systems: Design and Implementation, 3rd Edition by Andrew S. Tanenbaum_
