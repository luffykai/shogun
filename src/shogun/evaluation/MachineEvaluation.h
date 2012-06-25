/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Copyright (C) 2012 Jacob Walker
 */

#ifndef CMACHINEEVALUATION_H_
#define CMACHINEEVALUATION_H_

#include <shogun/base/SGObject.h>
#include <shogun/base/SGObject.h>
#include <shogun/evaluation/Evaluation.h>
#include <shogun/evaluation/EvaluationResult.h>
#include <shogun/evaluation/MachineEvaluation.h>

namespace shogun {

class CMachine;
class CFeatures;
class CLabels;
class CSplittingStrategy;
class CEvaluation;

class CMachineEvaluation: public CSGObject {

/* @brief Machine Evaluation is an abstract class
 * that evaluates a machine according to some criterion.
 *
 */

public:

	CMachineEvaluation();

	/** constructor
	 * @param machine learning machine to use
	 * @param features features to use for cross-validation
	 * @param labels labels that correspond to the features
	 * @param splitting_strategy splitting strategy to use
	 * @param evaluation_criterion evaluation criterion to use
	 * @param autolock whether machine should be auto-locked before evaluation
	 */
	CMachineEvaluation(CMachine* machine, CFeatures* features, CLabels* labels,
			CSplittingStrategy* splitting_strategy,
			CEvaluation* evaluation_criterion, bool autolock=true);

	/** constructor, for use with custom kernels (no features)
	 * @param machine learning machine to use
	 * @param labels labels that correspond to the features
	 * @param splitting_strategy splitting strategy to use
	 * @param evaluation_criterion evaluation criterion to use
	 * @param autolock autolock
	 */
	CMachineEvaluation(CMachine* machine, CLabels* labels,
			CSplittingStrategy* splitting_strategy,
			CEvaluation* evaluation_criterion, bool autolock=true);


	virtual ~CMachineEvaluation();

	/** Returns the name of the SGSerializable instance.  It MUST BE
	 *  the CLASS NAME without the prefixed `C'.
	 *
	 *  @return name of the SGSerializable
	 */
	virtual const char* get_name() const
	{
		return "MachineEvaluation";
	}

	/** @return in which direction is the best evaluation value? */
	EEvaluationDirection get_evaluation_direction();

	/** method for evaluation. Performs cross-validation.
	 * Is repeated m_num_runs. If this number is larger than one, a confidence
	 * interval is calculated if m_conf_int_alpha is (0<p<1).
	 * By default m_num_runs=1 and m_conf_int_alpha=0
	 *
	 * @return result of evaluation
	 */
	virtual CEvaluationResult* evaluate() = 0;

	/** @return underlying learning machine */
	CMachine* get_machine() const;

	/** setter for the autolock property. If true, machine will tried to be
	 * locked before evaluation */
	void set_autolock(bool autolock) { m_autolock=autolock; }

protected:

	virtual void init();

protected:
	CMachine* m_machine;
	CFeatures* m_features;
	CLabels* m_labels;
	CSplittingStrategy* m_splitting_strategy;
	CEvaluation* m_evaluation_criterion;

	/** whether machine will automaticall be locked before evaluation */
	bool m_autolock;

	/** whether machine should be unlocked after evaluation */
	bool m_do_unlock;

};

} /* namespace shogun */

#endif /* CMACHINEEVALUATION_H_ */
