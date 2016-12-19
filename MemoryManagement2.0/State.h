#ifndef STATE_H_
#define STATE_H_
//	状态模式

class RealRun;
class DIALOG2;

class State
{
public:
	virtual void OPT() {}
	virtual void LRU() {}
	virtual void FIFO() {}
	virtual void CurrentState(RealRun *war) {}
};


class RealRun
{
private:
	State *m_state;  
	friend class OPTState;
	friend class LRUState;
	friend class FIFOState;
	DIALOG2 *dlg2;
public:
	RealRun(State *state, DIALOG2* dlg) : m_state(state), dlg2(dlg) {}
	~RealRun() { delete m_state; }
	void SetState(State *state) { delete m_state; m_state = state; }
	void GetState() { m_state->CurrentState(this); }
};



class OPTState : public State
{
public:
	void OPT(RealRun *war) 
	{
		war->dlg2->OPT();
	}
	void CurrentState(RealRun *war) { OPT(war); }
};

class LRUState : public State
{
public:
	void LRU(RealRun *war) 
	{
		war->dlg2->LRU();
	}
	void CurrentState(RealRun *war) { LRU(war); }
};


class FIFOState : public State
{
public:
	void FIFO(RealRun *war) 
	{
		war->dlg2->FIFO();
	}
	void CurrentState(RealRun *war) { FIFO(war); }
};

#endif