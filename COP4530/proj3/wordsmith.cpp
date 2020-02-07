/*
  wordsmith.cpp

  Jon Crawford

  2/16/2018

  cpp file with implementations for the wordsmith API

*/

#include <wordsmith.h>
#include <cleanup.cpp>



WordSmith::WordSmith(): wordset_(), infiles_()
{
  std::cout << "\nWordSmith built using: " << this->set_type_string << " and Retrieve/Insert\n";
}

WordSmith::~WordSmith(){}

bool WordSmith::ReadText(const fsu::String& infile, bool showProgress)
{
  const size_t ticker = 65536;
  std::ifstream inData;
  inData.open(infile.Cstr());
  if(!inData) return false;
  
  fsu::String line;
  infiles_.PushBack(infile);
  
  size_t count = 0;
  while (inData >> line)
  {
    WordSmith::Cleanup(line);
    if(line.Length() == 0) continue;
    EntryType p(line,1);
    if(wordset_.Retrieve(p))
    {  
      ++(p.second_);
      wordset_.Insert(p);
    }
    else
    {
      wordset_.Insert(p);
    }  
    ++count;
    if(showProgress)
    {
      if(count % ticker == 0)
      {
        std::cout << "  ** reading progress : numwords == " << count << "\n";
      }
    }
  } // end while  
  
  inData.close();
  std::cout << "\n     Number of words read:    " << count << "\n"
            << "     Current vocabulary size: " << Vocab() << "\n";
  return true;

} // end ReadText

bool WordSmith::WriteReport(const fsu::String& outfile, unsigned short c1, unsigned short c2) const
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
          << std::left <<std::setw(c1) << "word"
          << std::right << std::setw(c2) << "frequency" << std::endl;
  outData << std::left << std::setw(c1) << "----"
          << std::right << std::setw(c2) << "---------" << std::endl;
  for(SetType::Iterator i = wordset_.Begin(); i != wordset_.End(); ++i)
  {
    outData << std::left  << std::setw(c1) << (*i).first_
            << std::right << std::setw(c2) << (*i).second_ << std::endl;  
  }  
  outData << "\nNumber of words: " << WordCount()   
          << "\nVocabulary size: " << Vocab() << std::endl;
  outData.close();
  std::cout << "\n     Number of words:         " << WordCount()
            << "\n     Vocabulary size:         " << Vocab() 
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
  std::cout << "\n     Current word count:      " << WordCount()
            << "\n     Current vocabulary size: " << Vocab() << "\n";
}

void WordSmith::ClearData()
{
  infiles_.Clear();
  wordset_.Clear();
}

size_t WordSmith::WordCount() const 
{
  size_t count = 0;
  for(SetType::Iterator i = wordset_.Begin(); i != wordset_.End(); ++i)
  {
    count += (*i).second_;
  }
  return count;
}


