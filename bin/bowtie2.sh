if [[ "$OSTYPE" =~ ^darwin ]]; then
  if [[ $(arch) =~ ^arm ]] || [[ $(arch) =~ ^aarch ]]; then
    echo "Current system is macOS arm64."
    echo "Searching for corresponding binary zip pack file."
    if $(ls -1 | grep "^bowtie2" | grep -q "macos-arm64.zip$") ; then
      binaryFile=$(ls -1 | grep "^bowtie2" | grep "macos-arm64.zip$")
    fi
  elif [[ $(arch) =~ ^x ]] && [[ $(arch) =~ 64 ]]; then
    echo "Current system is macOS x64."
    echo "Searching for corresponding binary zip pack file."
    if $(ls -1 | grep "^bowtie2" | grep -q "macos-x86_64.zip$") ; then
      binaryFile=$(ls -1 | grep "^bowtie2" | grep "macos-x86_64.zip$")
    fi
  else
    echo "System architecture is not identified."
    exit 2
  fi
elif [[ "$OSTYPE" =~ ^linux ]]; then
  if [[ $(arch) =~ ^arm ]] || [[ $(arch) =~ ^aarch ]]; then
    echo "Current system is Linux aarch64."
    echo "Searching for corresponding binary zip pack file."
    if $(ls -1 | grep "^bowtie2" | grep -q "linux-aarch64.zip$") ; then
      binaryFile=$(ls -1 | grep "^bowtie2" | grep "linux-aarch64.zip$")
    fi
  elif [[ $(arch) =~ ^x ]] && [[ $(arch) =~ 64 ]]; then
    echo "Current system is Linux x64."
    echo "Searching for corresponding binary zip pack file."
    if $(ls -1 | grep "^bowtie2" | grep -q "linux-x86_64.zip$") ; then
      binaryFile=$(ls -1 | grep "^bowtie2" | grep "linux-x86_64.zip$")
    fi
  else
    echo "System architecture is not identified."
    exit 2
  fi
else
  echo "System type is not identified."
  exit 1
fi

if [ -z "$binaryFile" ]; then
  echo "Binary zip pack not found."
  echo "You can download the binaries at http://bowtie-bio.sourceforge.net/bowtie2/index.shtml"
  exit 3
fi

echo "Zip binary file found."
echo "Unzipping binaries."

unzip "$binaryFile" -n

basepath=$(cd `dirname $0`; cd ..; pwd)

mkdir $basepath/data

./${binaryFile%.zip*}/bowtie2-build $1 $basepath/data/$2
./${binaryFile%.zip*}/bowtie2 -x $basepath/data/$2 -U $3 -S $basepath/data/$4