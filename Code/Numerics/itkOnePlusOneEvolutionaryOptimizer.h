/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkOnePlusOneEvolutionaryOptimizer.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 2002 Insight Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkOnePlusOneEvolutionaryOptimizer_h
#define __itkOnePlusOneEvolutionaryOptimizer_h

#include <itkSingleValuedNonLinearOptimizer.h>
#include <itkRandomVariateGeneratorBase.h>

namespace itk
{

/** \class OnePlusOneEvolutionaryOptimizer
 * \brief 1+1 evolutionary strategy optimizer
 *
 * This optimizer searches for the optimal parameters. It changes its search
 * radius and position using the grow factor ,shrink factor, and isotropic 
 * probability function (which is a random unit normal variate generator).   
 *
 * This optimizer needs a cost function and a random unit normal 
 * variate generator.
 * The cost function should return cost with new position in parameter space
 * which will be generated by 1+1 evolutionary strategy.
 * Users should plug-in the random unit normal variate generator using 
 * SetNormalVariateGenerator method.
 *
 * The SetEpsilon method is the minimum value for the frobenius_norm of 
 * the covariance matrix. If the fnorm is smaller than this value, 
 * the optimization process will stop even before it hits the maximum 
 * iteration.
 *
 * Another way to stop the optimization process is calling the 
 * StopOptimization method. At next iteration after calling it, the
 * optimization process will stop.
 *
 * This optimizing scheme was initially developed and implemented 
 * by Martin Styner, Univ. of North Carolina at Chapel Hill, and his
 * colleagues.
 *
 * For more details. refer to the following articles.
 * "Parametric estimate of intensity inhomogeneities applied to MRI" 
 * Martin Styner, G. Gerig, Christian Brechbuehler, Gabor Szekely,  
 * IEEE TRANSACTIONS ON MEDICAL IMAGING; 19(3), pp. 153-165, 2000, 
 * (http://www.cs.unc.edu/~styner/docs/tmi00.pdf)
 *
 * "Evaluation of 2D/3D bias correction with 1+1ES-optimization" 
 * Martin Styner, Prof. Dr. G. Gerig (IKT, BIWI, ETH Zuerich), TR-197
 * (http://www.cs.unc.edu/~styner/docs/StynerTR97.pdf)
 *
 * \ingroup Numerics Optimizers
 *
 * \sa NormalVariateGenerator 
 */

class ITK_EXPORT OnePlusOneEvolutionaryOptimizer: 
    public SingleValuedNonLinearOptimizer
{
public:
  /** Standard "Self" typedef. */
  typedef OnePlusOneEvolutionaryOptimizer     Self ;
  typedef SingleValuedNonLinearOptimizer      Superclass;
  typedef SmartPointer<Self>                  Pointer;
  typedef SmartPointer<const Self>            ConstPointer;
  
  /** Method for creation through the object factory. */
  itkNewMacro(Self);
 
  /** Run-time type information (and related methods). */
  itkTypeMacro(OnePlusOneEvolutionaryOptimizer, SingleValuedNonLinearOptimizer );
 
  /** Type of the Cost Function   */
  typedef  SingleValuedCostFunction         CostFunctionType;
  typedef  CostFunctionType::Pointer        CostFunctionPointer;

  /** Normal random variate generator type. */
  typedef Statistics::RandomVariateGeneratorBase NormalVariateGeneratorType ;
  
  /** Set if the Optimizer should Maximize the metric */
  void MaximizeOn() {m_Maximize=true;}

  /** Set/Get maximum iteration limit. */
  itkSetMacro( MaximumIteration, unsigned int );
  itkGetConstMacro( MaximumIteration, unsigned int );

  /** Get the search radius grow factor in parameter space. */
  itkGetConstMacro( GrowthFactor, double );

  /** Get search radius shrink factor. */
  itkGetConstMacro( ShrinkFactor, double );

  /** Get initial search radius in parameter space. */
  itkGetConstMacro( InitialRadius, double );

  /** Set/Get the minimal size of search radius 
   * (frobenius_norm of covariance matrix). */
  itkSetMacro( Epsilon, double );   
  itkGetConstMacro( Epsilon, double );   

  void SetNormalVariateGenerator(NormalVariateGeneratorType* generator) ;

  /** Initializes the optimizer.
   * Before running this optimizer, this function should have been called.
   *
   * initialRadius: search radius in parameter space
   * grow: search radius grow factor
   * shrink: searhc radius shrink factor */
  void Initialize(double initialRadius, double grow = -1, double shrink = -1) ;

  MeasureType GetCurrentCost()
  { return m_CurrentCost ; }

  itkGetConstMacro( CurrentIteration, unsigned int) ;
  /** Start optimization.
   * Optimization will stop when it meets either of two termination conditions,
   * the maximum iteration limit or epsilon (minimal search radius)  */
  void StartOptimization() ;

  /** when users call StartOptimization, this value will be set false.
   * By calling StopOptimization, this flag will be set true, and 
   * optimization will stop at the next iteration. */
  void StopOptimization() 
  { m_Stop = true ; }

protected:
  OnePlusOneEvolutionaryOptimizer() ;
  virtual ~OnePlusOneEvolutionaryOptimizer() ;
  void PrintSelf(std::ostream& os, Indent indent) const;

private:
  
  /** Smart pointer to the normal random variate generator. */
  NormalVariateGeneratorType* m_RandomGenerator ;

  /** Maximum iteration limit. */
  unsigned int m_MaximumIteration ;

  /** Current iteration */
  unsigned int m_CurrentIteration ;

  /** Set if the Metric should be maximized: Default = False */
  bool m_Maximize;

  /** The minimal size of search radius 
   * (frobenius_norm of covariance matrix). */ 
  double m_Epsilon ;

  /** Initial search radius in paramter space. */
  double m_InitialRadius ;

  /** Search radius growth factor in parameter space. */
  double m_GrowthFactor ;

  /** Search radius shrink factor in parameter space, */
  double m_ShrinkFactor ;

  /** Flag tells if the optimizer was initialized using Initialize function. */
  bool m_Initialized ;

  /** Internal storage for the value type / used as a cache  */
  MeasureType       m_CurrentCost;

  /** this is user-settable flag to stop optimization.
   * when users call StartOptimization, this value will be set false.
   * By calling StopOptimization, this flag will be set true, and 
   * optimization will stop at the next iteration. */
  bool m_Stop ;
} ; // end of class

} // end of namespace itk

#endif
