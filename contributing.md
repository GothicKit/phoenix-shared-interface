# how to contribute to this project

If you'd like to add a feature or fix a bug, you're more than welcome to help! You can grab one of the open issues and
start to work on it, too. 

There are some conventions I'd ask you to keep in mind while writing code for this project. I've outlined them below.

## conventions

There are a few things that should be followed to keep the codebase consistent.

### git

Your commits should be small. Avoid bundling multiple changes relating (for example) multiple different issues or bugs
into one commit. Rather, create multiple smaller commits, each self-contained only changing one part of the logic[^1].

Git commit should roughly follow the [Angular Commit Message Format](https://github.com/angular/angular/blob/main/CONTRIBUTING.md#commit).
The scope should be a comma-separated list of the names of the structures being changed.

[^2]: For example, if there is an issue with the VM and you change something, then add a new API to the `PxScript`, 
those should be two separate commits.

### c code

This project uses the following naming conventions:

* Structure names and Typedefs are `PascalCase` and prefixed with `Px`
* Internal APIs, such as opaque structures or function names start with `Internal_`.
* Function names are `camelCase`
* Member variables are `camelCase`

Use `clang-format`. While the CI pipeline will complain about noncompliance, you can avoid unnecessary commits by
checking your code before pushing.
