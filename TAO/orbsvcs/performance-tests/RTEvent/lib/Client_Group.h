/**
 * @file Client_Group.h
 *
 * @author Carlos O'Ryan <coryan@uci.edu>
 */

#ifndef TAO_PERF_RTEC_CLIENT_GROUP_H
#define TAO_PERF_RTEC_CLIENT_GROUP_H

#include "Servant_var.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "Client_Pair.h"
#include "Loopback_Pair.h"

/**
 * @class Client_Group
 *
 * @brief Simplify the initialization of a Supplier/Consumer pair
 *        connected through a Loopback.
 */
class TAO_RTEC_Perf_Export Client_Group
{
public:
  /// Constructor
  /**
   * We need a default constructor because this class is often used in
   * arrays.
   */
  Client_Group (void);

  /// Initialize the consumer/supplier pair(s)
  /**
   * @param experiment_id For tests that run multiple experiments
   *        this number is changed on each iteration, guaranteeing
   *        better isolation.
   * @param base_event_type The event type generated by the supplier.
   *        The Loopback_Consumer consumes the same event, the
   *        Loopback_Supplier generates (base_event_type + 1), and the
   *        consumer subscribes for that type too.
   * @param iterations The number of iterations expected on the test.
   * @param workload_in_usecs The consumer workload, in microseconds.
   * @param gsf The high resolution timer global scale factor.
   *
   */
  void init (CORBA::Long experiment_id,
             CORBA::Long base_event_type,
             CORBA::ULong iterations,
             CORBA::Long workload_in_usecs,
             ACE_High_Res_Timer::global_scale_factor_type gsf,
             PortableServer::POA_ptr supplier_poa,
             PortableServer::POA_ptr consumer_poa);

  /// Initialize the consumer/supplier pair(s)
  /**
   * @param event_type_range The supplier declares more events than it
   *        generates.
   */
  void init (CORBA::Long experiment_id,
             CORBA::Long base_event_type,
             CORBA::Long base_event_type_range,
             CORBA::ULong iterations,
             CORBA::Long workload_in_usecs,
             ACE_High_Res_Timer::global_scale_factor_type gsf,
             PortableServer::POA_ptr supplier_poa,
             PortableServer::POA_ptr consumer_poa);

  /// Connect to the event channel
  void connect (RtecEventChannelAdmin::EventChannel_ptr ec);

  /// Disconnect from the event channel
  void disconnect (void);

  //@{
  /** @name Accessors
   */
  Supplier *supplier () const;

  Consumer *consumer () const;

  Loopback_Supplier *loopback_supplier () const;

  Loopback_Consumer *loopback_consumer () const;
  //@}

private:
  Client_Pair client_pair_;
  Loopback_Pair loopback_pair_;
};

#if defined(__ACE_INLINE__)
#include "Client_Group.inl"
#endif /* __ACE_INLINE__ */

#endif /* TAO_PERF_RTEC_CLIENT_GROUP_H */
