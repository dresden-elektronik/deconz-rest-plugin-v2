/*
 * Copyright (c) 2017-2020 dresden elektronik ingenieurtechnik gmbh.
 * All rights reserved.
 *
 * The software in this package is published under the terms of the BSD
 * style license a copy of which has been included with this distribution in
 * the LICENSE.txt file.
 *
 */

#ifndef REST_NODE_BASE_H
#define REST_NODE_BASE_H

#include <QDateTime>
#include <deconz.h>

/*! \class NodeValue

    Holds bookkeeping data for numeric ZCL values.
 */
class NodeValue
{
public:
    enum UpdateType { UpdateInvalid, UpdateByZclReport, UpdateByZclRead };

    NodeValue() :
        updateType(UpdateInvalid),
        endpoint(0),
        clusterId(0),
        attributeId(0),
        minInterval(0),
        maxInterval(0),
        zclSeqNum(0)
    {
        value.u64 = 0;
    }
    bool isValid() const { return updateType != UpdateInvalid; }

    QDateTime timestamp;
    QDateTime timestampLastReport;
    QDateTime timestampLastReadRequest;
    QDateTime timestampLastConfigured;
    UpdateType updateType;
    quint8 endpoint;
    quint16 clusterId;
    quint16 attributeId;
    quint16 minInterval;
    quint16 maxInterval;
    quint8 zclSeqNum; // sequence number for configure reporting
    deCONZ::NumericUnion value;
};


/*! \class RestNodeBase

    The base class for all device representations.
 */
class RestNodeBase
{
public:
    RestNodeBase();
    virtual ~RestNodeBase();
    deCONZ::Node *node();
    void setNode(deCONZ::Node *node);
    deCONZ::Address &address();
    const deCONZ::Address &address() const;
    virtual bool isAvailable() const;
    bool needSaveDatabase() const;
    void setNeedSaveDatabase(bool needSave);
    const QString &id() const;
    void setId(const QString &id);
    const QString &uniqueId() const;
    void setUniqueId(const QString &uid);
    bool mustRead(uint32_t readFlags);
    void enableRead(uint32_t readFlags);
    void clearRead(uint32_t readFlags);
    const QTime &nextReadTime(uint32_t item) const;
    void setNextReadTime(uint32_t item, const QTime &time);
    int lastRead(uint32_t item) const;
    void setLastRead(uint32_t item, int lastRead);
    int lastAttributeReportBind() const;
    void setLastAttributeReportBind(int lastBind);
    bool mgmtBindSupported() const;
    void setMgmtBindSupported(bool supported);
    void setZclValue(NodeValue::UpdateType updateType, quint8 endpoint, quint16 clusterId, quint16 attributeId, const deCONZ::NumericUnion &value);
    const NodeValue &getZclValue(quint16 clusterId, quint16 attributeId, quint8 endpoint = 0) const;
    NodeValue &getZclValue(quint16 clusterId, quint16 attributeId, quint8 endpoint = 0);
    std::vector<NodeValue> &zclValues();
    const std::vector<NodeValue> &zclValues() const;
    const QDateTime &lastRx() const;
    void rx();
    
    // APIv2
    uint16_t nwkv2() const;
    uint64_t extv2() const;
    void setManufacturerv2(const QString &manufacturer);
    void setModelIdv2(const QString &modelid);
    void setDateCodev2(const QString &datecode);
    void setSwVersionv2(const QString &swversion);
    const QString &manufacturerv2() const;
    const QString &modelIdv2() const;
    const QString &dateCodev2() const;
    const QString &swVersionv2() const;
    bool isCoordinatorv2() const;
    bool isRouterv2() const;
    bool isEndDevicev2() const;
    bool isZombiev2() const;
    const std::vector<uint8_t> &endpointsv2() const;
    const QList<deCONZ::SimpleDescriptor> &simpleDescriptorsv2() const;
    bool debugNode() const;
    void setDebugNode(bool nodeEnabled);
    bool debugAll() const;
    void setDebugAll(bool allEnabled);
    bool isFfdv2() const;
    bool isMainsPoweredv2() const;
    bool isReceiverOnWhenIdlev2() const;
    uint16_t manufacturerCodev2() const;
    QString namev2() const;
    void setName(QString deviceName);

private:
    deCONZ::Node *m_node;
    deCONZ::Address m_addr;
    QString m_id;
    QString m_uid;
    bool m_mgmtBindSupported;
    bool m_needSaveDatabase;

    uint32_t m_read; // bitmap of READ_* flags
    std::vector<int> m_lastRead; // copy of idleTotalCounter
    int m_lastAttributeReportBind; // copy of idleTotalCounter
    std::vector<QTime> m_nextReadTime;
    QDateTime m_lastRx;

    NodeValue m_invalidValue;
    std::vector<NodeValue> m_values;
    QTime m_invalidTime;
    
    // APIv2
    QString m_manufacturer;
    QString m_model;
    QString m_datecode;
    QString m_sw_version;
    bool m_debugNode;
    bool m_debugAll;
    QString m_name;
};

#endif // REST_NODE_BASE_H
