/*
  wordsmith2.cpp

  Jon Crawford

  2/28/2018

  cpp file with implementations for the wordsmith2 API

*/

#include <wordsmith2.h>
#include <cleanup.cpp>

WordSmith::WordSmith(): frequency_(), infiles_(), globalCount_(0)
{
  //std::cout << "\nWordSmith built using: " << this->set_type_string << " and Retrieve/Insert\n";
}

WordSmith::~WordSmith(){}

bool WordSmith::ReadText(const fsu::String& infile, bool showProgress)
{
  const size_t ticker = 65536;
  std::ifstream inData;
  inData.open(infile.Cstr());
  if(!inData) return false;
  size_t frequency = frequency_.Size();
  fsu::String str;
  infiles_.PushBack(infile);
  
  size_t numwords = 0;
  while (inData >> str)
  {
    Cleanup(str);
    if (str.Length() != 0)
    {
      ++frequency_[str];
      ++numwords;
    } // end if
    if(showProgress)
    {
      if(numwords % ticker == 0)
      {
        std::cout << "  ** reading progress : numwords == " << numwords << "\n";
      }
    }
  } //end while 
  globalCount_ += numwords;
  inData.close();
  std::cout << "\n     Number of words read:    " << numwords << "\n"
            << "     New words in vocabulary: " << frequency_.Size() - frequency << "\n";
  return true;

} // end ReadText

bool WordSmith::WriteReport(const fsu::String& outfile, unsigned short kw, unsigned short dw,
                            std::ios_base::fmtflags kf, std::ios_base::fmtflags df) const
{
  std::ofstream outData (outfile.Cstr());
  if (!outData) return false;
  if (infiles_.Empty())
  {
    outData.close();
    return true;
  }  
  outData << "Text Analysis for files: ";
  for (fsu::ConstListIterator<fsu::String> i = infiles_.Begin(); i != infiles_.End(); )
  {
    outData << *i;
    if (++i != infiles_.End()) outData << ", ";
  }
  outData << "\n\n"
          << std::left <<std::setw(kw) << "word"
          << std::right << std::setw(dw) << "frequency" << std::endl;
  outData << std::left << std::setw(kw) << "----"
          << std::right << std::setw(dw) << "---------" << std::endl;
  frequency_.Display(outData,kw,dw,kf,df);
  outData << "\nNumber of words: " << globalCount_   
          << "\nVocabulary size: " << frequency_.Size() << std::endl;
  outData.close();
  std::cout << "\n     Number of words:         " << globalCount_
            << "\n     Vocabulary size:         " << frequency_.Size() 
            << "\n     Analysis written to file " << outfile << "\n";
  return true;

} // end WriteReport

void WordSmith::ShowSummary() const
{
  std::cout << "\n     Current files:           ";
  for (fsu::ConstListIterator<fsu::String> i = infiles_.Begin(); i != infiles_.End(); )
  {
    std::cout << *i;
    if (++i != infiles_.End()) std::cout << ", ";
  }
  std::cout << "\n     Current word count:      " << globalCount_
            << "\n     Current vocabulary size: " << frequency_.Size() << "\n\n";
}

void WordSmith::ClearData()
{
  infiles_.Clear();
  globalCount_ = 0;
  frequency_.Clear();
}

