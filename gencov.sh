lcov --directory objs --capture --output-file objs/app.info
genhtml --output-directory output --title "SemVer" objs/app.info