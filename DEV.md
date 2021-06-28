# Gearworks Engine: Development log
This file details the history in development of the Gearworks Engine.

## Formatting
When adding logs to this file, the following formatting system will be used:

### Use of the date
When logging a new version, the date of the version creation should be noted in **DD/MM/YYYY** format: `23/07/2022`
### Version numbering
- For **development** versions, list the version number with a 'd' character before it: `version d1.12`.
- For **release** versions, simply list the version number on its own, but note the word "release" before "version": `release version 2.3`.
- For **experimental** versions, list the **major** number on its own, and include the word "experimental": `experimental version 6`.<sup>1</sup>
### Types of updates
- When a **major** feature has been added, use the symbol `[++]`.
- When a **minor** feature has been added, use the symbol `[+]`.
- When a **bug** has been fixed, use the symbol `[!]`.
- When a **feature** of any type has been removed, use the symbol `[-]`
### Combining this formatting
With this formatting system, a new version log should look like this in the Markdown editor:<sup>2</sup>
```
### 23/07/2022 - experimental version `13`:
- \[++] Made the program _really_ good
- \[+] Made the program good
- \[!] Fixed a bug where the program was bad
- \[-] Removed the bad stuff from the program
```
If there are versions of the same type made in the same day, change `experimental version '13'` to `experimental versions '13' - '16'`. However, if the versions are of different types, e.g. release and development, log them seperately. However, any versions of any type that are created on different days should be logged seperately.

## Version logs
### 27/06/2021 - versions `d1.0` - `d1.1`:
- \[++] Started development
- \[+] Implemented shader parsing and compilation.
### 28/06/2021 - versions `d1.2`:
- \[++] Added VertexBufferObject handling
- \[+] Refactored by adding some more comments and summary tags

## Footnotes
- <sup>1</sup> This numbering system is due to the limited number of experimental releases; a major and minor number system is simple not necessary.
- <sup>2</sup> It is important to ensure the back-slashes before the brackets so that links are not created.
