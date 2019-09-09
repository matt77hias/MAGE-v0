# Contributing to MAGE

Please read the [Code of Conduct](CODE_OF_CONDUCT.md), before contributing to MAGE.

## How to create an Issue
You may use the Issue Tracker to submit bug reports, feature requests or suggestions. You may ask for help or advice as well. However, please read this wall of text before doing so. The amount of incomplete or ambiguous requests due to people not following those guidelines is often overwhelming. Please do your best to clarify your request.

**Prerequisites:**
* Please read the [FAQ](Meta/faq.md).
* Please use the Search function of GitHub to look for similar issues. You may also browse issues by tags.
* Please use the Search function of your IDE to search in the code for comments related to your situation.
* If you get an assert or exception, use a debugger to locate the condition triggering it and read the comments around it.

**Guidelines to report an issue or ask a question:**
* Please provide your MAGE version number and/or the latest git commit id and branch.
* Please provide the relevant configuration(s) (e.g., Release, Debug) and platform(s) (e.g., x86, x64) and/or the relevant compiler and linker settings.
* Please state if you have made substantial modifications to your copy of MAGE.
* Try to be explicit with your Goals, your Expectations and what you have Tried. What you have in mind or in your code is not obvious to other people. People frequently discuss problems without first mentioning their goal.
* If you are discussing an assert, exception or crash, please provide a debugger callstack and/or the automatically generated minidump file. Never state "it crashes" without additional information. If you do not know how to use a debugger and retrieve a callstack, learning about it will be useful.
* Please provide a Minimal, Complete and Verifiable Example ([MCVE](https://stackoverflow.com/help/mcve)) to demonstrate your problem. Narrowing your problem to its shortest and purest form is the easiest way to understand it. Please test your shortened code to ensure it actually exhibits the problem. Often while creating the MCVE you will end up solving the problem! Many questions that are missing a standalone verifiable example are missing the actual cause of their issue in the description, which ends up wasting everyone's time.
* Try to attach screenshots to clarify the context. They often convey useful information that are omitted by the description. You can drag pictures/files here (prefer Github attachments over 3rd party hosting).
* When requesting a new feature, please describe the usage context (how you intend to use it, why you need it, etc.).

If you have been using MAGE for a while *or* have been using C++ for several years *or* have demonstrated good behavior here, it is ok to not fullfill every item to the letter. Those are guidelines and experienced users or members of the community will know which information is useful in a given context.

## How to create an Pull Request
* When adding a feature, please describe the usage context (how you intend to use it, why you need it, etc.).
* When fixing a warning or compilation problem, please post the compiler log and specify the MAGE version you are using.
* Try to attach screenshots to clarify the context and demonstrate the feature at a glance. You can drag pictures/files here (prefer Github attachments over 3rd party hosting).
* Make sure your code adheres the [Code Guidelines](Meta/code-guidelines.md).
* Make sure you create a branch for the pull request. In Git, one pull request is associated to one branch. If you keep pushing to the same branch after you submitted the pull request, your new commits will appear in the pull request (we can still cherry-pick individual commits).

Thank you for reading! Thank you for contributing! 🧙
