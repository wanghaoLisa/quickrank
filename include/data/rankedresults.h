/*
 * QuickRank - A C++ suite of Learning to Rank algorithms
 * Webpage: http://quickrank.isti.cnr.it/
 * Contact: quickrank@isti.cnr.it
 *
 * Unless explicitly acquired and licensed from Licensor under another
 * license, the contents of this file are subject to the Reciprocal Public
 * License ("RPL") Version 1.5, or subsequent versions as allowed by the RPL,
 * and You may not copy or use this file in either source code or executable
 * form, except in compliance with the terms and conditions of the RPL.
 *
 * All software distributed under the RPL is provided strictly on an "AS
 * IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, AND
 * LICENSOR HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE, QUIET ENJOYMENT, OR NON-INFRINGEMENT. See the RPL for specific
 * language governing rights and limitations under the RPL.
 *
 * Contributor:
 *   HPC. Laboratory - ISTI - CNR - http://hpc.isti.cnr.it/
 */
#ifndef QUICKRANK_DATA_RANKEDRESULTS_H_
#define QUICKRANK_DATA_RANKEDRESULTS_H_

#include <memory>
#include <boost/noncopyable.hpp>
#include <boost/container/vector.hpp>

#include "types.h"
#include "queryresults.h"

namespace quickrank {
namespace data {

/// This class generates a ranked list of results.
///
/// This class does not carry information about the actual features,
/// but only about the labels and the scores generated by a ranker
/// (this is why this is not (yet) a subclass of QueryResults).
class RankedResults : private boost::noncopyable {
 public:

  /// Generates a Ranked Results list.
  ///
  /// This is actually used to sort QueryResults and to store
  /// labels and scores in sorted order.
  /// It generates a copy of original data and scores
  /// which might be useful for caching.
  /// It also provides an un-mapping function.
  /// \param n_instances The number of training instances (lines) in the dataset.
  /// \param n_features The number of features.
  RankedResults(std::shared_ptr<QueryResults> results, Score* scores);
  virtual ~RankedResults();

  // provide some kinf od unmap function ?

  Label* sorted_labels() const {
    return labels_;
  }

  Score* sorted_scores() const {
    return scores_;
  }

  const unsigned int pos_of_rank(const unsigned int rank) const {
    return unmap_[rank];
  }

  const unsigned int num_results() const {
    return num_results_;
  }

 private:
  Label* labels_ = NULL;
  Score* scores_ = NULL;
  unsigned int num_results_;
  unsigned int* unmap_ = NULL;
};

}  // namespace data
}  // namespace quickrank

#endif
