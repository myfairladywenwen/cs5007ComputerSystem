# Here is myOtherScript.sh that will:
# 1. go to resources directory and pull from the repo
# 2. let the user choose which directory to copy
# 3. make a new directory under wenxie_CS5006(to test whether the script works well)
# 4. go to wenxie_CS5006 and ls all the items


cd ~/cs5007/resources  # go to resourses directory
git pull               # pull from repo
ls                     # list files
echo which directory you want to copy    # ask user which directory to copy
read toCopy                              # read in as a variable
cd ~/cs5007/wenxie_CS5006                # go to wenxie_CS5006
mkdir newlyCopied                        # make a new directory named "newlyCopied"
cp -r ~/cs5007/resources/$toCopy ~/cs5007/wenxie_CS5006/newlyCopied  # copy the source directory to the target
cd ~/cs5007/wenxie_CS5006                # go to wenxie_CS5006
ls                                       # list files
# usage:sh myOtherScript.sh
