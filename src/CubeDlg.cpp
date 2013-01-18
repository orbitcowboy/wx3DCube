#include "CubeDlg.hpp"
#include <wx/pen.h>
BEGIN_EVENT_TABLE(CubeDlg, wxDialog)
    EVT_CLOSE(CubeDlg::OnClose)
    EVT_SIZE(CubeDlg::CubeDlgSize)
    EVT_PAINT(CubeDlg::CubeDlgPaint)
    EVT_TIMER(ID_WXTIMER1, CubeDlg::OnTimer)
END_EVENT_TABLE()

CubeDlg::CubeDlg(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
    : wxDialog(parent, id, title, position, size, style)
{
    CreateGUIControls();
}

CubeDlg::~CubeDlg()
{
}

void CubeDlg::CreateGUIControls()
{
    SetIcon(wxNullIcon);
    SetSize(8, 8, 509, 412);
    Center();

	// --------------------------------------------------
    //  	 7 - - - - - 6
    //     / |  	   / |
    //    4 - - - - - 5  |
    //    |  |  	  |  |
    //    |  3 - - - -|- 2
    //    | /		  | /
    //    0 - - - - - 1
	// --------------------------------------------------
    // init member variables
	const double dCubeSideLength = 100;
    m_p[0][X] = -dCubeSideLength; m_p[0][Y] = -dCubeSideLength; m_p[0][Z] = -dCubeSideLength;
    m_p[1][X] = +dCubeSideLength; m_p[1][Y] = -dCubeSideLength; m_p[1][Z] = -dCubeSideLength;
    m_p[2][X] = +dCubeSideLength; m_p[2][Y] = -dCubeSideLength; m_p[2][Z] = +dCubeSideLength;
    m_p[3][X] = -dCubeSideLength; m_p[3][Y] = -dCubeSideLength; m_p[3][Z] = +dCubeSideLength;
    m_p[4][X] = -dCubeSideLength; m_p[4][Y] = +dCubeSideLength; m_p[4][Z] = -dCubeSideLength;
    m_p[5][X] = +dCubeSideLength; m_p[5][Y] = +dCubeSideLength; m_p[5][Z] = -dCubeSideLength;
    m_p[6][X] = +dCubeSideLength; m_p[6][Y] = +dCubeSideLength; m_p[6][Z] = +dCubeSideLength;
    m_p[7][X] = -dCubeSideLength; m_p[7][Y] = +dCubeSideLength; m_p[7][Z] = +dCubeSideLength;

    // y-Werte spiegeln
    for (int i=0;i<8;++i) 
        m_p[i][Y] = -m_p[i][Y];

	m_angle_x = 0.01;
	m_angle_y = 0.0075;
	m_angle_z = 0.005;

    m_timer = new wxTimer();
    m_timer->SetOwner(this, ID_WXTIMER1);
    m_timer->Start(50);
}

void CubeDlg::OnClose(wxCloseEvent& WXUNUSED(event))
{
    Destroy();
}

void CubeDlg::CubeDlgPaint(wxPaintEvent& WXUNUSED(event))
{
    SetBackgroundStyle(wxBG_STYLE_CUSTOM);
    wxBufferedPaintDC dc(this);

    // Get window dimensions
    wxSize sz = GetClientSize();
	// determine the center of the canvas
    const wxPoint center(wxPoint(sz.x / 2, sz.y / 2));

    // create background color
    wxColour powderblue = wxColour(176,224,230);

    // draw powderblue background
    dc.SetPen(powderblue);
    dc.SetBrush(powderblue);
    dc.DrawRectangle(0, 0, sz.x, sz.y);


    // draw clock border
	wxPen Pen(*wxBLACK_PEN);
	Pen.SetWidth(1);
    dc.SetPen(Pen);
    dc.SetBrush(*wxBLACK_BRUSH);

    // initial cube coordinates:
    // --> use center.x (center.y) to ensure the cube stays allways in the center of the canvas
    dc.DrawLine((int)(m_p[0][X])+center.x,(int)(m_p[0][Y])+center.y,(int)(m_p[1][X])+center.x,(int)(m_p[1][Y])+center.y);
    dc.DrawLine((int)(m_p[1][X])+center.x,(int)(m_p[1][Y])+center.y,(int)(m_p[2][X])+center.x,(int)(m_p[2][Y])+center.y);
    dc.DrawLine((int)(m_p[2][X])+center.x,(int)(m_p[2][Y])+center.y,(int)(m_p[3][X])+center.x,(int)(m_p[3][Y])+center.y);
    dc.DrawLine((int)(m_p[3][X])+center.x,(int)(m_p[3][Y])+center.y,(int)(m_p[0][X])+center.x,(int)(m_p[0][Y])+center.y);
    dc.DrawLine((int)(m_p[4][X])+center.x,(int)(m_p[4][Y])+center.y,(int)(m_p[5][X])+center.x,(int)(m_p[5][Y])+center.y);
    dc.DrawLine((int)(m_p[5][X])+center.x,(int)(m_p[5][Y])+center.y,(int)(m_p[6][X])+center.x,(int)(m_p[6][Y])+center.y);
    dc.DrawLine((int)(m_p[6][X])+center.x,(int)(m_p[6][Y])+center.y,(int)(m_p[7][X])+center.x,(int)(m_p[7][Y])+center.y);
    dc.DrawLine((int)(m_p[7][X])+center.x,(int)(m_p[7][Y])+center.y,(int)(m_p[4][X])+center.x,(int)(m_p[4][Y])+center.y);
    dc.DrawLine((int)(m_p[0][X])+center.x,(int)(m_p[0][Y])+center.y,(int)(m_p[4][X])+center.x,(int)(m_p[4][Y])+center.y);
    dc.DrawLine((int)(m_p[1][X])+center.x,(int)(m_p[1][Y])+center.y,(int)(m_p[5][X])+center.x,(int)(m_p[5][Y])+center.y);
    dc.DrawLine((int)(m_p[2][X])+center.x,(int)(m_p[2][Y])+center.y,(int)(m_p[6][X])+center.x,(int)(m_p[6][Y])+center.y);
    dc.DrawLine((int)(m_p[3][X])+center.x,(int)(m_p[3][Y])+center.y,(int)(m_p[7][X])+center.x,(int)(m_p[7][Y])+center.y);

/*
	DrawPolygon(dc, 0,1,2,3);
	DrawPolygon(dc, 6,5,4,7);
	DrawPolygon(dc, 5,1,0,4);
	DrawPolygon(dc, 3,2,6,7);
	DrawPolygon(dc, 2,1,5,6);
	DrawPolygon(dc, 4,0,3,7);
*/

	// perspective: z = 1 + p[z]/1000
	double c[8];

	 // Perspektive: *1+z/1000000
    for (int i=0;i<8;i++) 
	{
        c[i] = 1+m_p[i][Z]/100000;
    }

    // Kreuzprodukt der eine Flaeche aufspannenden Vektoren bilden
    // Wenn Betrag der z-Koordinate positiv: Flaeche anzeigen
    if(((m_p[0][X]*c[0]-m_p[1][X]*c[1])*(m_p[2][Y]*c[2]-m_p[1][Y]*c[1])
       -(m_p[0][Y]*c[0]-m_p[1][Y]*c[1])*(m_p[2][X]*c[2]-m_p[1][X]*c[1])) > 0) 
	{
        // |1->0 x 1->2| > 0
		wxPoint pt[4];
		pt[0].x = (m_p[0][X]*c[0])+center.x;
		pt[1].x = (m_p[1][X]*c[1])+center.x;
		pt[2].x = (m_p[2][X]*c[2])+center.x;
		pt[3].x = (m_p[3][X]*c[3])+center.x;

		pt[0].y = (m_p[0][Y]*c[0])+center.y;
		pt[1].y = (m_p[1][Y]*c[1])+center.y;
		pt[2].y = (m_p[2][Y]*c[2])+center.y;
		pt[3].y = (m_p[3][Y]*c[3])+center.y;
    	dc.SetBrush(*wxRED_BRUSH);
		dc.DrawPolygon(4,pt);
    }
    else if(((m_p[6][X]*c[6]-m_p[5][X]*c[5])*(m_p[4][Y]*c[4]-m_p[5][Y]*c[5])
            -(m_p[6][Y]*c[6]-m_p[5][Y]*c[5])*(m_p[4][X]*c[4]-m_p[5][X]*c[5])) > 0) 
	{
		// |5->6 x 5->4| > 0
		wxPoint pt[4];
		pt[0].x = (m_p[4][X]*c[4])+center.x;
		pt[1].x = (m_p[5][X]*c[5])+center.x;
		pt[2].x = (m_p[6][X]*c[6])+center.x;
		pt[3].x = (m_p[7][X]*c[7])+center.x;

		pt[0].y = (m_p[4][Y]*c[4])+center.y;
		pt[1].y = (m_p[5][Y]*c[5])+center.y;
		pt[2].y = (m_p[6][Y]*c[6])+center.y;
		pt[3].y = (m_p[7][Y]*c[7])+center.y;
    	dc.SetBrush(*wxRED_BRUSH);
		dc.DrawPolygon(4,pt);
    }

    if(((m_p[5][X]*c[5]-m_p[1][X]*c[1])*(m_p[0][Y]*c[0]-m_p[1][Y]*c[1])
       -(m_p[5][Y]*c[5]-m_p[1][Y]*c[1])*(m_p[0][X]*c[0]-m_p[1][X]*c[1])) > 0) 
	{
        //|1->5 x 1->0| > 0
		wxPoint pt[4];
		pt[0].x = (m_p[0][X]*c[0])+center.x;
		pt[1].x = (m_p[1][X]*c[1])+center.x;
		pt[2].x = (m_p[5][X]*c[5])+center.x;
		pt[3].x = (m_p[4][X]*c[4])+center.x;

		pt[0].y = (m_p[0][Y]*c[0])+center.y;
		pt[1].y = (m_p[1][Y]*c[1])+center.y;
		pt[2].y = (m_p[5][Y]*c[5])+center.y;
		pt[3].y = (m_p[4][Y]*c[4])+center.y;
    	dc.SetBrush(*wxGREEN_BRUSH);
		dc.DrawPolygon(4,pt);
    }
    else if(((m_p[3][X]*c[3]-m_p[2][X]*c[2])*(m_p[6][Y]*c[6]-m_p[2][Y]*c[2])
            -(m_p[3][Y]*c[3]-m_p[2][Y]*c[2])*(m_p[6][X]*c[6]-m_p[2][X]*c[2])) > 0) 
	{
		// |2->3 x 2->6| > 0
		wxPoint pt[4];
		pt[0].x = (m_p[3][X]*c[3])+center.x;
		pt[1].x = (m_p[2][X]*c[2])+center.x;
		pt[2].x = (m_p[6][X]*c[6])+center.x;
		pt[3].x = (m_p[7][X]*c[7])+center.x;

		pt[0].y = (m_p[3][Y]*c[3])+center.y;
		pt[1].y = (m_p[2][Y]*c[2])+center.y;
		pt[2].y = (m_p[6][Y]*c[6])+center.y;
		pt[3].y = (m_p[7][Y]*c[7])+center.y;
    	dc.SetBrush(*wxGREEN_BRUSH);
		dc.DrawPolygon(4,pt);
    }

    if(((m_p[2][X]*c[2]-m_p[1][X]*c[1])*(m_p[5][Y]*c[5]-m_p[1][Y]*c[1])
       -(m_p[2][Y]*c[2]-m_p[1][Y]*c[1])*(m_p[5][X]*c[5]-m_p[1][X]*c[1])) > 0) 
	{
        //|1->5 x 1->0| > 0
		wxPoint pt[4];
		pt[0].x = (m_p[1][X]*c[1])+center.x;
		pt[1].x = (m_p[2][X]*c[2])+center.x;
		pt[2].x = (m_p[6][X]*c[6])+center.x;
		pt[3].x = (m_p[5][X]*c[5])+center.x;

		pt[0].y = (m_p[1][Y]*c[1])+center.y;
		pt[1].y = (m_p[2][Y]*c[2])+center.y;
		pt[2].y = (m_p[6][Y]*c[6])+center.y;
		pt[3].y = (m_p[5][Y]*c[5])+center.y;
    	dc.SetBrush(*wxBLUE_BRUSH);
		dc.DrawPolygon(4,pt);
    }
    else if(((m_p[4][X]*c[4]-m_p[0][X]*c[0])*(m_p[3][Y]*c[3]-m_p[0][Y]*c[0])
            -(m_p[4][Y]*c[4]-m_p[0][Y]*c[0])*(m_p[3][X]*c[3]-m_p[0][X]*c[0])) > 0) 
	{
		// |2->3 x 2->6| > 0
		wxPoint pt[4];
		pt[0].x = (m_p[0][X]*c[0])+center.x;
		pt[1].x = (m_p[3][X]*c[3])+center.x;
		pt[2].x = (m_p[7][X]*c[7])+center.x;
		pt[3].x = (m_p[4][X]*c[4])+center.x;

		pt[0].y = (m_p[0][Y]*c[0])+center.y;
		pt[1].y = (m_p[3][Y]*c[3])+center.y;
		pt[2].y = (m_p[7][Y]*c[7])+center.y;
		pt[3].y = (m_p[4][Y]*c[4])+center.y;
    	dc.SetBrush(*wxBLUE_BRUSH);
		dc.DrawPolygon(4,pt);
    }	

}
double rad2deg(double rad)
{
      return (180.0 * rad / (M_PI));
}

void CubeDlg::DrawPolygon(wxBufferedPaintDC &dc, const unsigned int &i, const unsigned int &j, const unsigned int &k, const unsigned int &h)
{
	// perspective: z = 1 + p[z]/1000
	double c[8];

	 // Perspektive: *1+z/1000000
    for (int iIndex=0;iIndex<8;iIndex++) 
	{
        c[i] = 1+m_p[iIndex][Z]/100000;
    }

    // Get window dimensions
    wxSize sz = GetClientSize();
	// determine the center of the canvas
    const wxPoint center(wxPoint(sz.x / 2, sz.y / 2));

	if(((m_p[i][X]*c[i]-m_p[j][X]*c[j])*(m_p[k][Y]*c[k]-m_p[j][Y]*c[j])
       -(m_p[i][Y]*c[i]-m_p[j][Y]*c[j])*(m_p[k][X]*c[k]-m_p[j][X]*c[j])) > 0) 
	{
            // |j->i x j->k| > 0
		wxPoint pt[4];
		pt[0].x = (m_p[i][X]*c[i])+center.x;
		pt[1].x = (m_p[j][X]*c[j])+center.x;
		pt[2].x = (m_p[k][X]*c[k])+center.x;
		pt[3].x = (m_p[h][X]*c[h])+center.x;

		pt[0].y = (m_p[i][Y]*c[i])+center.y;
		pt[1].y = (m_p[j][Y]*c[j])+center.y;
		pt[2].y = (m_p[k][Y]*c[k])+center.y;
		pt[3].y = (m_p[h][Y]*c[h])+center.y;

        // Winkel zwischen dem Vektor (v1,v2,v3), der senkrecht auf der Flaeche steht
        // und dem Einheitsvektor in Richtung der Beleuchtungsquelle (0,0,1)
        // (d.h. Licht von vorne) bestimmt die Helligkeit der Flaeche.
        const double v1 = (m_p[i][Y]-m_p[j][Y])*(m_p[k][Z]-m_p[j][Z])
                         -(m_p[i][Z]-m_p[j][Z])*(m_p[k][Y]-m_p[j][Y]);
        const double v2 = (m_p[i][Z]-m_p[j][Z])*(m_p[k][X]-m_p[j][X])
                         -(m_p[i][X]-m_p[j][X])*(m_p[k][Z]-m_p[j][Z]);
        const double v3 = (m_p[i][X]-m_p[j][X])*(m_p[k][Y]-m_p[j][Y])
                         -(m_p[i][Y]-m_p[j][Y])*(m_p[k][X]-m_p[j][X]);

    	const int deg(rad2deg(asin(sqrt((v2*v2+v1*v1)/(v1*v1+v2*v2+v3*v3)))));

		wxBrush Brush(wxColour(220-deg, 220-deg, 220-deg));
    	dc.SetBrush(Brush);
		dc.DrawPolygon(4,pt);
	}
}

void CubeDlg::CubeDlgSize(wxSizeEvent& WXUNUSED(event))
{
    Refresh();
}

void CubeDlg::OnTimer(wxTimerEvent& WXUNUSED(event))
{
	 double px, py, pz;

	 // rotate
	 for (unsigned int i=0;i<8;i++) 
	 {
	 	 px = m_p[i][X];
	 	 py = m_p[i][Y];
	 	 pz = m_p[i][Z];

	 	 // Rotate x-axis
	 	 m_p[i][Y] = py*cos(m_angle_x)-pz*sin(m_angle_x);
	 	 m_p[i][Z] = py*sin(m_angle_x)+pz*cos(m_angle_x);

	 	 py = m_p[i][Y];
	 	 pz = m_p[i][Z];

	 	 // Rotate y-axis
	 	 m_p[i][X] = px*cos(m_angle_y)+pz*sin(m_angle_y);
	 	 m_p[i][Z] =-px*sin(m_angle_y)+pz*cos(m_angle_y);

	 	 px = m_p[i][X];

	 	 // Rotate z-axis
	 	 m_p[i][X] = px*cos(m_angle_z)-py*sin(m_angle_z);
	 	 m_p[i][Y] = py*cos(m_angle_z)+px*sin(m_angle_z);
	 }

	// force refresh
    Refresh();
}
