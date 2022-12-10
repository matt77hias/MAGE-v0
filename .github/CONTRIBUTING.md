<img align="left" src="https://github.com/matt77hias/MAGE-v0-Meta/blob/master/res/MAGE.png" width="120px"/>

# Contributing to MAGE

[How to create an issue](#SS-How-to-create-an-issue) - [How to create an pull request](#SS-How-to-create-a-pull-request)

Please read the [Code of Conduct](CODE_OF_CONDUCT.md) before contributing to MAGE.

## <a name="SS-How-to-create-an-issue"></a>How to create an issue
You may use the Issue Tracker to submit bug reports, feature requests or suggestions. You may ask for help or advice as well. However, please read this wall of text before doing so. The amount of incomplete or ambiguous requests due to people not following those guidelines is often overwhelming. Please do your best to clarify your request.

**Prerequisites:**
* Please read the [FAQ](../MAGE/Meta/FrequentlyAskedQuestions.md).
* Please use the search function of GitHub to look for similar issues. You may also browse issues by tags.
* Please use the search function of your IDE to search in the code for comments related to your issue.
* If you get an assert or exception, use a debugger to locate the condition triggering it and read the comments around it.

**Guidelines to report an issue or ask a question:**
* Please provide your MAGE version number and/or the latest git commit id and branch.
* Please provide the relevant configuration(s) (_e.g., Release, Debug_) and platform(s) (_e.g., x86, x64_) and/or the relevant compiler and linker settings.
* Please state if you have made substantial modifications to your copy of MAGE.
* Try to be explicit with your goals, your expectations and what you have tried. What you have in mind or in your code is not obvious to other people. People frequently discuss problems without first mentioning their goal.
* If you are discussing an assert, exception or crash, please provide a debugger callstack and/or the automatically generated minidump file. Never state "it crashes" without additional information. If you do not know how to use a debugger and retrieve a callstack, learning about it will be useful.
* Please provide a Minimal, Complete and Verifiable Example ([MCVE](https://stackoverflow.com/help/mcve)) to demonstrate your problem. Narrowing your problem to its shortest and purest form is the easiest way to understand it. Please test your shortened code to ensure it actually exhibits the problem. Often while creating the MCVE you will end up solving the problem! Many questions that are missing a standalone verifiable example are missing the actual cause of their issue in the description, which ends up wasting everyone's time.
* Try to attach screenshots to clarify the context. They often convey useful information that are omitted by the description. You can drag pictures/files here (prefer Github attachments over 3rd party hosting).
* When requesting a new feature, please describe the usage context (_e.g., how you intend to use it, why you need it, etc._).

If you have been using MAGE for a while *or* have been using C++ for several years *or* have demonstrated good behavior here, it is ok to not fullfill every item to the letter. Those are guidelines and experienced users or members of the community will know which information is useful in a given context.

## <a name="SS-How-to-create-a-pull-request"></a>How to create a pull request (PR)

**Prerequisites:**
* Please use the search function of GitHub to look for similar/related pull requests and issues. You may also browse issues by tags.

**Guidelines to create a pull request:**
* Please understand that by submitting a pull request you are also submitting a request for the maintainer to review your code and then take over its maintenance forever. Therefore, it is important that pull requests ease the maintainer into understanding and accepting them (on top of the possible benefits for the end-users).
* Many pull requests are useful to demonstrate a need and a possible solution but are not adequate for merging (_e.g., causing other issues, not seeing other aspects of the big picture, etc._). In doubt, do not hesitate to push a pull request because that is always the first step toward finding the mergeable solution! Even if a pull request stays unmerged for a long time, its presence can be useful for other users and helps toward finding a general solution.
* **When adding a feature**, please describe the usage context (_e.g., how you intend to use it, why you need it, etc._).
* **When fixing a warning or compilation problem**, please post the compiler log and specify the MAGE version you are using.
* Try to attach screenshots to clarify the context and demonstrate the feature at a glance. You can drag pictures/files here (prefer Github attachments over 3rd party hosting).
* Make sure your code adheres the [Code Guidelines](../MAGE/Meta/CodeGuidelines.md).
* Make sure you create a branch for the pull request. In Git, one pull request is associated to one branch. If you keep pushing to the same branch after you submitted the pull request, your new commits will appear in the pull request (we can still cherry-pick individual commits).

Thank you for reading! Thank you for contributing! 🧙
